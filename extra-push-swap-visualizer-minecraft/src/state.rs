use std::time::SystemTime;

use tokio::runtime::Runtime;
use tokio::sync::mpsc;

use valence::prelude::*;

#[derive(Resource)]
pub struct RuntimeResource {
    pub runtime: Runtime,
}

impl Default for RuntimeResource {
    fn default() -> Self {
        info!("Creating new Tokio runtime");
        Self {
            runtime: Runtime::new().expect("Failed to create Tokio runtime"),
        }
    }
}

#[derive(Debug)]
pub enum PushSwapStatus {
    NotStarted,
    Executing,
    Failed(String),
    Completed(Vec<String>),
}

#[derive(Resource)]
pub struct PushSwapChannel {
    pub sender: mpsc::Sender<(Entity, PushSwapStatus)>,
    pub receiver: mpsc::Receiver<(Entity, PushSwapStatus)>,
}

impl Default for PushSwapChannel {
    fn default() -> Self {
        info!("Creating new push swap channel");
        let (sender, receiver) = mpsc::channel(32);
        Self { sender, receiver }
    }
}

#[derive(Component)]
pub struct VisualizerState {
    pub array_a: Vec<i32>,
    pub array_b: Vec<i32>,
    pub wall_offset_a: BlockPos,
    pub wall_offset_b: BlockPos,
    pub last_click: f64,
    pub pending_instructions: Option<Vec<String>>,
    pub is_sorting: bool,
    pub push_swap_status: PushSwapStatus,
    pub last_status_check: SystemTime,
    pub last_instruction_time: f64,
    pub current_instruction_index: usize,
}

impl Default for VisualizerState {
    fn default() -> Self {
        info!("Creating new visualizer state");
        Self {
            array_a: Vec::new(),
            array_b: Vec::new(),
            wall_offset_a: BlockPos::default(),
            wall_offset_b: BlockPos::default(),
            last_click: 0.0,
            pending_instructions: None,
            is_sorting: false,
            push_swap_status: PushSwapStatus::NotStarted,
            last_status_check: SystemTime::now(),
            last_instruction_time: 0.0,
            current_instruction_index: 0,
        }
    }
}

pub fn execute_initial_push_swap(
    mut clients: Query<(Entity, &mut VisualizerState, &mut Client), Added<Client>>,
    channel: Res<PushSwapChannel>,
    runtime: Res<RuntimeResource>,
) {
    use crate::utils::generate_random_array;

    for (entity, mut state, mut client) in clients.iter_mut() {
        info!("Executing initial push_swap for new client");
        let numbers = generate_random_array();
        state.push_swap_status = PushSwapStatus::Executing;

        // Store the initial array in array_a
        state.array_a = numbers.clone();
        state.push_swap_status = PushSwapStatus::Executing;

        // Spawn the push_swap execution task
        let sender = channel.sender.clone();
        let entity = entity;
        runtime.runtime.spawn(async move {
            info!("Spawned push_swap execution task");
            match crate::push_swap::execute_push_swap(&numbers).await {
                Ok(output) => {
                    info!("Push_swap execution completed successfully");
                    let instructions: Vec<String> = output.lines().map(|s| s.to_string()).collect();
                    let _ = sender
                        .send((entity, PushSwapStatus::Completed(instructions)))
                        .await;
                }
                Err(e) => {
                    error!("Push_swap execution failed: {}", e);
                    let _ = sender
                        .send((entity, PushSwapStatus::Failed(e.to_string())))
                        .await;
                }
            }
        });

        client.send_chat_message("Executing initial push_swap...".color(Color::DARK_PURPLE));
    }
}

/// Check for incoming push_swap status updates and handle them
/// appropriately. This system will update the client's state
/// and send chat messages to the client as needed.
///
/// ## Parameters
///
/// - `clients`: Query of all entities with VisualizerState and Client components
/// - `channel`: Resource containing the push_swap channel
pub fn check_push_swap_status(
    mut clients: Query<(&mut VisualizerState, &mut Client)>,
    mut channel: ResMut<PushSwapChannel>,
) {
    // Handle incoming status updates
    while let Ok((entity, new_status)) = channel.receiver.try_recv() {
        if let Ok((mut state, mut client)) = clients.get_mut(entity) {
            match new_status {
                PushSwapStatus::Failed(error) => {
                    error!("Push swap execution failed: {}", error);
                    client.send_chat_message(
                        format!("Push swap execution failed: {}", error).color(Color::RED),
                    );
                    state.push_swap_status = PushSwapStatus::NotStarted;
                }
                PushSwapStatus::Completed(instructions) => {
                    info!(
                        "Push swap execution completed with {} instructions",
                        instructions.len()
                    );
                    client.send_chat_message(
                        "Push swap execution completed successfully!".color(Color::DARK_PURPLE),
                    );
                    state.pending_instructions = Some(instructions);
                    state.current_instruction_index = 0;
                    state.is_sorting = true;
                    state.last_instruction_time = 0.0; // This will trigger first instruction immediately
                    state.push_swap_status = PushSwapStatus::NotStarted;
                }
                _ => {}
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::{PushSwapStatus, VisualizerState};
    use valence::prelude::*;

    #[test]
    fn test_visualizer_state_default_values() {
        let state = VisualizerState::default();

        assert!(state.array_a.is_empty());
        assert!(state.array_b.is_empty());
        assert_eq!(state.wall_offset_a, BlockPos::default());
        assert_eq!(state.wall_offset_b, BlockPos::default());
        assert_eq!(state.last_click, 0.0);
        assert!(state.pending_instructions.is_none());
        assert!(!state.is_sorting);
        assert!(matches!(state.push_swap_status, PushSwapStatus::NotStarted));
        assert_eq!(state.current_instruction_index, 0);
    }

    #[test]
    fn test_push_swap_status_transitions() {
        // Test transition to Executing
        let status = PushSwapStatus::Executing;
        assert!(matches!(status, PushSwapStatus::Executing));

        // Test transition to Failed
        let error_msg = "Test error".to_string();
        let status = PushSwapStatus::Failed(error_msg.clone());
        if let PushSwapStatus::Failed(msg) = status {
            assert_eq!(msg, error_msg);
        } else {
            panic!("Expected Failed status");
        }

        // Test transition to Completed
        let instructions = vec!["sa".to_string(), "pb".to_string()];
        let status = PushSwapStatus::Completed(instructions.clone());
        if let PushSwapStatus::Completed(inst) = status {
            assert_eq!(inst, instructions);
        } else {
            panic!("Expected Completed status");
        }
    }

    #[test]
    fn test_visualizer_state_array_operations() {
        let mut state = VisualizerState::default();

        // Test array A operations
        state.array_a = vec![1, 2, 3];
        assert_eq!(state.array_a.len(), 3);
        assert_eq!(state.array_a[0], 1);

        // Test array B operations
        state.array_b = vec![4, 5];
        assert_eq!(state.array_b.len(), 2);
        assert_eq!(state.array_b[0], 4);
    }

    #[test]
    fn test_visualizer_state_instruction_management() {
        let mut state = VisualizerState::default();

        let instructions = vec!["sa".to_string(), "pb".to_string(), "ra".to_string()];
        state.pending_instructions = Some(instructions.clone());
        state.is_sorting = true;

        assert!(state.pending_instructions.is_some());
        assert_eq!(state.pending_instructions.as_ref().unwrap().len(), 3);
        assert!(state.is_sorting);

        // Test instruction progression
        state.current_instruction_index = 1;
        assert_eq!(state.current_instruction_index, 1);
        assert_eq!(
            state.pending_instructions.as_ref().unwrap()[state.current_instruction_index],
            "pb"
        );
    }
}

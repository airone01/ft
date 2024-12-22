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
}

impl Default for VisualizerState {
    fn default() -> Self {
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
        let numbers = generate_random_array();
        state.push_swap_status = PushSwapStatus::Executing;

        // Spawn the push_swap execution task
        let sender = channel.sender.clone();
        let entity = entity;

        runtime.runtime.spawn(async move {
            match crate::push_swap::execute_push_swap(&numbers).await {
                Ok(output) => {
                    let instructions: Vec<String> = output.lines().map(|s| s.to_string()).collect();
                    let _ = sender
                        .send((entity, PushSwapStatus::Completed(instructions)))
                        .await;
                }
                Err(e) => {
                    let _ = sender
                        .send((entity, PushSwapStatus::Failed(e.to_string())))
                        .await;
                }
            }
        });

        client.send_chat_message("Executing initial push_swap...".color(Color::DARK_PURPLE));
    }
}

// System to check push_swap status periodically
pub fn check_push_swap_status(
    mut clients: Query<(&mut VisualizerState, &mut Client)>,
    mut channel: ResMut<PushSwapChannel>,
) {
    // Handle incoming status updates
    while let Ok((entity, new_status)) = channel.receiver.try_recv() {
        if let Ok((mut state, mut client)) = clients.get_mut(entity) {
            match new_status {
                PushSwapStatus::Failed(error) => {
                    client.send_chat_message(
                        format!("Push swap execution failed: {}", error).color(Color::RED),
                    );
                    state.push_swap_status = PushSwapStatus::NotStarted;
                }
                PushSwapStatus::Completed(instructions) => {
                    client.send_chat_message(
                        "Push swap execution completed successfully!".color(Color::DARK_PURPLE),
                    );
                    state.pending_instructions = Some(instructions);
                    state.push_swap_status = PushSwapStatus::NotStarted;
                }
                _ => {}
            }
        }
    }
}

use tokio::sync::mpsc;
use valence::prelude::*;

#[derive(Resource)]
pub struct PushSwapChannel {
    pub receiver: mpsc::Receiver<(Entity, Vec<String>)>,
    pub sender: mpsc::Sender<(Entity, Vec<String>)>,
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
}

pub fn check_push_swap_results(
    mut channel: ResMut<PushSwapChannel>,
    mut clients: Query<(&mut Client, &mut VisualizerState)>,
) {
    if let Ok((entity, instructions)) = channel.receiver.try_recv() {
        if let Ok((mut client, mut state)) = clients.get_mut(entity) {
            state.pending_instructions = Some(instructions);
            client.send_chat_message("Starting visualization...".color(Color::GREEN));
        }
    }
}

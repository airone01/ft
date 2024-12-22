use super::visualize_array;
use crate::push_swap::execute_push_swap;
use crate::state::{PushSwapChannel, VisualizerState};
use crate::utils::generate_random_array;
use valence::interact_block::InteractBlockEvent;
use valence::prelude::*;

pub fn handle_click(
    mut clients: Query<(Entity, &mut Client, &mut VisualizerState, &mut ChunkLayer)>,
    mut interact_block: EventReader<InteractBlockEvent>,
    channel: Res<PushSwapChannel>,
) {
    for event in interact_block.read() {
        if let Ok((entity, mut client, mut state, _)) = clients.get_mut(event.client) {
            client.send_chat_message("Running...");

            let current_time = std::time::SystemTime::now()
                .duration_since(std::time::UNIX_EPOCH)
                .unwrap()
                .as_secs_f64();

            if state.is_sorting || current_time - state.last_click < 1.0 {
                continue;
            }
            state.last_click = current_time;
            state.is_sorting = true;

            client.send_chat_message("Loading push_swap results...".color(Color::YELLOW));

            // let numbers = state.array_a.clone();
            let numbers = generate_random_array();
            let entity = entity;
            let sender = channel.sender.clone();

            tokio::spawn(async move {
                if let Ok(output) = execute_push_swap(&numbers).await {
                    let instructions: Vec<String> = output.lines().map(|s| s.to_string()).collect();
                    let _ = sender.send((entity, instructions)).await;
                }
            });
        }
    }
}

pub fn process_instructions(
    mut clients: Query<(&mut Client, &mut VisualizerState, &mut ChunkLayer)>,
) {
    for (mut client, mut state, mut layer) in clients.iter_mut() {
        if let Some(instructions) = state.pending_instructions.take() {
            for instruction in instructions {
                match instruction.trim() {
                    "pa" => {
                        if !state.array_b.is_empty() {
                            let value = state.array_b.remove(0);
                            state.array_a.insert(0, value);
                        }
                    }
                    "pb" => {
                        if !state.array_a.is_empty() {
                            let value = state.array_a.remove(0);
                            state.array_b.insert(0, value);
                        }
                    }
                    "ra" => {
                        if !state.array_a.is_empty() {
                            state.array_a.rotate_left(1);
                        }
                    }
                    "rb" => {
                        if !state.array_b.is_empty() {
                            state.array_b.rotate_left(1);
                        }
                    }
                    "rra" => {
                        if !state.array_a.is_empty() {
                            state.array_a.rotate_right(1);
                        }
                    }
                    "rrb" => {
                        if !state.array_b.is_empty() {
                            state.array_b.rotate_right(1);
                        }
                    }
                    "sa" => {
                        if state.array_a.len() >= 2 {
                            state.array_a.swap(0, 1);
                        }
                    }
                    "sb" => {
                        if state.array_b.len() >= 2 {
                            state.array_b.swap(0, 1);
                        }
                    }
                    _ => {
                        client.send_chat_message(
                            format!("Unknown command: {}", instruction).italic(),
                        );
                    }
                }

                visualize_array(&state.array_a, state.wall_offset_a, &mut layer);
                visualize_array(&state.array_b, state.wall_offset_b, &mut layer);

                std::thread::sleep(std::time::Duration::from_millis(100));
            }

            client.send_chat_message("Sorting complete!".color(Color::GREEN));
            state.is_sorting = false;
        }
    }
}

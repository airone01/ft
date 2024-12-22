use crate::state::{PushSwapStatus, VisualizerState};
use crate::utils::generate_random_array;
use crate::{PushSwapChannel, RuntimeResource};
use valence::interact_block::InteractBlockEvent;
use valence::prelude::*;

pub fn handle_click(
    mut clients: Query<(Entity, &mut Client, &mut VisualizerState), With<Client>>,
    mut interact_block: EventReader<InteractBlockEvent>,
    channel: Res<PushSwapChannel>,
    runtime: Res<RuntimeResource>,
) {
    for event in interact_block.read() {
        if let Ok((entity, mut client, mut state)) = clients.get_mut(event.client) {
            let current_time = std::time::SystemTime::now()
                .duration_since(std::time::UNIX_EPOCH)
                .unwrap()
                .as_secs_f64();

            // Check if we're already processing something or clicked too recently
            match state.push_swap_status {
                PushSwapStatus::Executing => {
                    client.send_chat_message("Already processing a sort...".color(Color::YELLOW));
                    continue;
                }
                _ if current_time - state.last_click < 1.0 => {
                    client.send_chat_message(
                        "Please wait a moment before clicking again".color(Color::YELLOW),
                    );
                    continue;
                }
                _ => {}
            }

            state.last_click = current_time;

            // Generate new random array and start execution
            let numbers = generate_random_array();
            state.push_swap_status = PushSwapStatus::Executing;

            client.send_chat_message("Starting new sort...".color(Color::YELLOW));

            // Spawn the push_swap execution task
            let sender = channel.sender.clone();
            let entity = entity;

            runtime.runtime.spawn(async move {
                match crate::push_swap::execute_push_swap(&numbers).await {
                    Ok(output) => {
                        let instructions: Vec<String> =
                            output.lines().map(|s| s.to_string()).collect();
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
        }
    }
}

pub fn process_instructions(
    mut clients: Query<(&mut Client, &mut VisualizerState, &mut ChunkLayer)>,
) {
    for (mut client, mut state, mut layer) in clients.iter_mut() {
        if let Some(instructions) = state.pending_instructions.take() {
            state.is_sorting = true;

            for instruction in instructions.clone() {
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
                            format!("Unknown command: {}", instruction)
                                .color(Color::rgb(234, 88, 12))
                                .italic(),
                        );
                    }
                }

                // Update visualization
                use crate::visualizer::visualize_array;
                visualize_array(&state.array_a, state.wall_offset_a, &mut layer);
                visualize_array(&state.array_b, state.wall_offset_b, &mut layer);

                std::thread::sleep(std::time::Duration::from_millis(100));
            }

            client.send_chat_message(
                "Sorting complete!".color(Color::GREEN)
                    + " (".color(Color::GRAY)
                    + instructions.len().into_text().color(Color::AQUA)
                    + " instructions)".color(Color::RESET),
            );
            state.is_sorting = false;
        }
    }
}

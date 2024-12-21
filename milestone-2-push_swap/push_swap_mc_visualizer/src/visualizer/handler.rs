use valence::message::SendMessage as _;
use valence::prelude::IntoText as _;
use valence::text::Color;
use valence::{
    client::Client,
    interact_block::InteractBlockEvent,
    prelude::{Entity, EventReader, Query},
    ChunkLayer,
};

use crate::utils::generate_random_array;
use crate::visualize_array;
use crate::{push_swap::execute_push_swap, VisualizerState};

pub fn handle_click(
    mut clients: Query<(Entity, &mut Client, &mut VisualizerState, &mut ChunkLayer)>,
    mut interact_block: EventReader<InteractBlockEvent>,
) {
    for event in interact_block.read() {
        if let Ok((_entity, mut client, mut state, mut layer)) = clients.get_mut(event.client) {
            let current_time = std::time::SystemTime::now()
                .duration_since(std::time::UNIX_EPOCH)
                .unwrap()
                .as_secs_f64();

            // Prevent multiple executions within 1 second
            if current_time - state.last_click < 1.0 {
                continue;
            }
            state.last_click = current_time;

            // Execute push_swap
            client.send_chat_message("Executing push_swap...".color(Color::YELLOW));
            match execute_push_swap(&generate_random_array()) {
                Ok(output) => {
                    client.send_chat_message(
                        "Input: >".into_text()
                            + state
                                .array_a
                                .iter()
                                .map(|n| n.to_string())
                                .collect::<Vec<String>>()
                                .join(" ")
                                .color(Color::LIGHT_PURPLE)
                            + "<",
                    );
                    client.send_chat_message(
                        "Output: >".into_text() + output.clone().color(Color::LIGHT_PURPLE) + "<",
                    );

                    // Parse and execute commands
                    for line in output.lines() {
                        match line.trim() {
                            "pa" => {
                                if !state.array_b.is_empty() {
                                    let value = state.array_b.pop().unwrap();
                                    state.array_a.push(value);
                                }
                            }
                            "pb" => {
                                if !state.array_a.is_empty() {
                                    let value = state.array_a.pop().unwrap();
                                    state.array_b.push(value);
                                }
                            }
                            "ra" => {
                                if !state.array_a.is_empty() {
                                    let value = state.array_a.remove(0);
                                    state.array_a.push(value);
                                }
                            }
                            "rb" => {
                                if !state.array_b.is_empty() {
                                    let value = state.array_b.remove(0);
                                    state.array_b.push(value);
                                }
                            }
                            "rra" => {
                                if !state.array_a.is_empty() {
                                    let value = state.array_a.pop().unwrap();
                                    state.array_a.insert(0, value);
                                }
                            }
                            "rrb" => {
                                if !state.array_b.is_empty() {
                                    let value = state.array_b.pop().unwrap();
                                    state.array_b.insert(0, value);
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
                                    format!("Unknown command: {}", line).italic(),
                                );
                            }
                        }

                        // Update visualization after each operation
                        visualize_array(&state.array_a, state.wall_offset_a, &mut layer);
                        visualize_array(&state.array_b, state.wall_offset_b, &mut layer);

                        // Add a small delay to make the visualization visible
                        std::thread::sleep(std::time::Duration::from_millis(100));
                    }

                    client.send_chat_message("Sorting complete!".italic());
                }
                Err(e) => {
                    client.send_chat_message(format!("Error executing push_swap: {}", e).italic());
                }
            }
        }
    }
}

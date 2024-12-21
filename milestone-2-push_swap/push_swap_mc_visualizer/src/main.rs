#![allow(clippy::type_complexity)]

use std::net::SocketAddr;
use std::process::Command;

use valence::interact_block::InteractBlockEvent;
use valence::inventory::PlayerAction;
use valence::network::{
    async_trait, BroadcastToLan, ConnectionMode, HandshakeData, PlayerSampleEntry, ServerListPing,
};
use valence::prelude::*;
use valence::spawn::IsFlat;
use valence::MINECRAFT_VERSION;

const START_POS: BlockPos = BlockPos::new(0, 100, 0);
const VIEW_DIST: u8 = 10;
const PLATFORM_SIZE: i32 = 4;
const ARRAY_SIZE: i32 = 10;
const MAX_HEIGHT: i32 = 50; // Maximum height for visualization

// Different colored blocks for visualization
const VISUALIZATION_BLOCKS: [BlockState; 12] = [
    BlockState::RED_WOOL,
    BlockState::RED_CONCRETE_POWDER,
    BlockState::ORANGE_CONCRETE,
    BlockState::ORANGE_WOOL,
    BlockState::ORANGE_CONCRETE_POWDER,
    BlockState::YELLOW_CONCRETE,
    BlockState::LIME_WOOL,
    BlockState::LIME_CONCRETE,
    BlockState::GREEN_CONCRETE_POWDER,
    BlockState::CYAN_WOOL,
    BlockState::BLUE_CONCRETE_POWDER,
    BlockState::BLUE_WOOL,
];

struct SortingVisualizerServer;

#[async_trait]
impl NetworkCallbacks for SortingVisualizerServer {
    async fn server_list_ping(
        &self,
        _shared: &SharedNetworkState,
        _remote_addr: SocketAddr,
        handshake_data: &HandshakeData,
    ) -> ServerListPing {
        ServerListPing::Respond {
            online_players: 69,
            max_players: 420,
            player_sample: vec![PlayerSampleEntry {
                name: "Made by elagouch @ 42 Lyon".into(),
                id: Uuid::from_u128(12345),
            }],
            description: "A push_swap visualizer ".into_text()
                + "IN MINECRAFT".color(Color::rgb(50, 50, 250))
                + "\nBecause why the fuck not",
            favicon_png: include_bytes!("../assets/logo-64x64.png"),
            version_name: ("Valence ".color(Color::GOLD) + MINECRAFT_VERSION.color(Color::RED))
                .to_legacy_lossy(),
            protocol: handshake_data.protocol_version,
        }
    }

    async fn broadcast_to_lan(&self, _shared: &SharedNetworkState) -> BroadcastToLan {
        BroadcastToLan::Enabled("Hello Valence!".into())
    }
}

#[derive(Component)]
struct VisualizerState {
    array_a: Vec<i32>,
    array_b: Vec<i32>,
    wall_offset_a: BlockPos,
    wall_offset_b: BlockPos,
    last_click: f64,
}

fn create_backdrop(wall_offset_a: BlockPos, wall_offset_b: BlockPos, layer: &mut ChunkLayer) {
    let total_width = (wall_offset_b.x - wall_offset_a.x) + MAX_HEIGHT + 4;
    let total_height = ARRAY_SIZE + 4;

    // Create black wall
    for x in 0..total_width {
        for y in 0..total_height {
            let pos = BlockPos::new(
                wall_offset_a.x - x + 2 + MAX_HEIGHT,
                wall_offset_a.y + y - 2,
                wall_offset_a.z + 1,
            );
            layer.set_block(pos, BlockState::BLACK_CONCRETE);
        }
    }
}

fn generate_random_array() -> Vec<i32> {
    let mut array = Vec::with_capacity(ARRAY_SIZE as usize);
    for i in 0..ARRAY_SIZE {
        array.push(i + 1);
    }
    use rand::seq::SliceRandom;
    let mut rng = rand::thread_rng();
    array.shuffle(&mut rng);
    array
}

fn get_block_color(value: i32) -> BlockState {
    // Map value to color based on its magnitude
    let index =
        ((value as f32 / ARRAY_SIZE as f32) * (VISUALIZATION_BLOCKS.len() - 1) as f32) as usize;
    VISUALIZATION_BLOCKS[index]
}

fn create_platform(layer: &mut ChunkLayer) {
    for x in -PLATFORM_SIZE..=PLATFORM_SIZE {
        for z in -PLATFORM_SIZE..=PLATFORM_SIZE {
            let platform_pos = BlockPos::new(START_POS.x + x, START_POS.y, START_POS.z + z);
            layer.set_block(platform_pos, BlockState::BLACK_STAINED_GLASS);
        }
    }
    for x in (-PLATFORM_SIZE + 1)..=(PLATFORM_SIZE - 1) {
        for z in (-PLATFORM_SIZE + 1)..=(PLATFORM_SIZE - 1) {
            let platform_pos = BlockPos::new(START_POS.x + x, START_POS.y, START_POS.z + z);
            layer.set_block(platform_pos, BlockState::BARRIER);
        }
    }
    layer.set_block(START_POS, BlockState::RED_STAINED_GLASS);
}

fn visualize_array(array: &[i32], wall_offset: BlockPos, layer: &mut ChunkLayer) {
    // Clear previous visualization
    for x in 0..MAX_HEIGHT {
        for y in 0..ARRAY_SIZE {
            let pos = BlockPos::new(wall_offset.x - x, wall_offset.y + y, wall_offset.z);
            layer.set_block(pos, BlockState::AIR);
        }
    }

    // Create new visualization
    for (i, &value) in array.iter().enumerate() {
        let width = (value as f32 / ARRAY_SIZE as f32 * MAX_HEIGHT as f32) as i32;
        let block_type = get_block_color(value);

        for x in 0..width {
            let pos = BlockPos::new(
                wall_offset.x - x,        // Changed to subtract x to make bars start from the left
                wall_offset.y + i as i32, // Removed the reversal so bars start from bottom
                wall_offset.z,
            );
            layer.set_block(pos, block_type);
        }
    }
}

fn execute_push_swap(numbers: &[i32]) -> Result<String, std::io::Error> {
    // Convert numbers to string arguments
    let args: Vec<String> = numbers.iter().map(|n| n.to_string()).collect();

    // Execute push_swap
    let output = Command::new("./push_swap").args(&args).output()?;

    // Convert output to string
    Ok(String::from_utf8_lossy(&output.stdout).into_owned())
}

fn init_clients(
    mut clients: Query<
        (
            Entity,
            &mut Client,
            &mut VisibleChunkLayer,
            &mut IsFlat,
            &mut GameMode,
        ),
        Added<Client>,
    >,
    server: Res<Server>,
    dimensions: Res<DimensionTypeRegistry>,
    biomes: Res<BiomeRegistry>,
    mut commands: Commands,
) {
    for (entity, mut client, mut visible_chunk_layer, mut is_flat, mut game_mode) in &mut clients {
        visible_chunk_layer.0 = entity;
        is_flat.0 = true;
        *game_mode = GameMode::Creative;

        client.send_chat_message("Welcome to Push Swap Visualizer!".italic());
        client.send_chat_message("Left click to start sorting!".italic());

        let random_array = generate_random_array();
        let empty_array = Vec::new(); // Stack B starts empty

        let wall_offset_a = BlockPos::new(
            START_POS.x,
            START_POS.y - (ARRAY_SIZE as f32 * 0.5).floor() as i32,
            START_POS.z + 50,
        );
        let wall_offset_b = BlockPos::new(
            START_POS.x + 50,
            START_POS.y - (ARRAY_SIZE as f32 * 0.5).floor() as i32,
            START_POS.z + 50,
        );

        let state = VisualizerState {
            array_a: random_array.clone(),
            array_b: empty_array,
            wall_offset_a,
            wall_offset_b,
            last_click: 0.0,
        };

        let mut layer = ChunkLayer::new(ident!("overworld"), &dimensions, &biomes, &server);

        create_platform(&mut layer);
        create_backdrop(state.wall_offset_a, state.wall_offset_b, &mut layer);
        visualize_array(&state.array_a, state.wall_offset_a, &mut layer);
        visualize_array(&state.array_b, state.wall_offset_b, &mut layer);

        commands.entity(entity).insert((state, layer));
    }
}

fn reset_clients(
    mut clients: Query<(
        &mut Client,
        &mut Position,
        &mut Look,
        &mut VisualizerState,
        &mut ChunkLayer,
    )>,
) {
    for (mut _client, mut pos, mut look, state, mut layer) in &mut clients {
        if state.is_added() {
            // Init chunks
            for pos in ChunkView::new(START_POS.into(), VIEW_DIST).iter() {
                layer.insert_chunk(pos, UnloadedChunk::new());
            }

            // Reset platform, backdrop and visualization
            create_platform(&mut layer);
            create_backdrop(state.wall_offset_a, state.wall_offset_b, &mut layer);
            visualize_array(&state.array_a, state.wall_offset_a, &mut layer);
            visualize_array(&state.array_b, state.wall_offset_b, &mut layer);

            // Position player for optimal viewing
            pos.set([
                f64::from(START_POS.x) + 0.5,
                f64::from(START_POS.y) + 1.0,
                f64::from(START_POS.z) + 0.5,
            ]);
            look.yaw = 0.0;
            look.pitch = 0.0;
        }
    }
}

fn manage_chunks(mut clients: Query<(&Position, &OldPosition, &mut ChunkLayer), With<Client>>) {
    for (pos, old_pos, mut layer) in &mut clients {
        let old_view = ChunkView::new(old_pos.get().into(), VIEW_DIST);
        let view = ChunkView::new(pos.0.into(), VIEW_DIST);

        if old_view != view {
            for pos in old_view.diff(view) {
                layer.remove_chunk(pos);
            }

            for pos in view.diff(old_view) {
                layer.chunk_entry(pos).or_default();
            }
        }
    }
}

fn handle_click(
    mut clients: Query<(Entity, &mut Client, &mut VisualizerState, &mut ChunkLayer)>,
    mut interact_block: EventReader<InteractBlockEvent>,
) {
    for event in interact_block.read() {
        if let Ok((entity, mut client, mut state, mut layer)) = clients.get_mut(event.client) {
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
            match execute_push_swap(&state.array_a) {
                Ok(output) => {
                    client.send_chat_message("Executing push_swap...".italic());

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

pub fn main() {
    App::new()
        .insert_resource(NetworkSettings {
            connection_mode: ConnectionMode::Offline,
            callbacks: SortingVisualizerServer.into(),
            ..Default::default()
        })
        .add_plugins(DefaultPlugins)
        .add_systems(
            Update,
            (
                init_clients,
                reset_clients.after(init_clients),
                manage_chunks.after(reset_clients),
                handle_click,
                despawn_disconnected_clients,
            ),
        )
        .run();
}

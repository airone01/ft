#![allow(clippy::type_complexity)]

use std::net::SocketAddr;

use rand::seq::SliceRandom;
use rand::Rng;
use valence::network::{
    async_trait, BroadcastToLan, ConnectionMode, HandshakeData, PlayerSampleEntry, ServerListPing,
};
use valence::prelude::*;
use valence::spawn::IsFlat;
use valence::MINECRAFT_VERSION;

const START_POS: BlockPos = BlockPos::new(0, 90, 0);
const VIEW_DIST: u8 = 10;
const PLATFORM_SIZE: i32 = 4;
const ARRAY_SIZE: i32 = 100;
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

#[derive(Component)]
struct VisualizerState {
    array: Vec<i32>,
    wall_offset: BlockPos, // Position where the visualization wall starts
}

pub fn main() {
    App::new()
        .insert_resource(NetworkSettings {
            connection_mode: ConnectionMode::Offline,
            callbacks: MyCallbacks.into(),
            ..Default::default()
        })
        .add_plugins(DefaultPlugins)
        .add_systems(
            Update,
            (
                init_clients,
                reset_clients.after(init_clients),
                manage_chunks.after(reset_clients),
                despawn_disconnected_clients,
            ),
        )
        .run();
}

struct MyCallbacks;

#[async_trait]
impl NetworkCallbacks for MyCallbacks {
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

fn create_platform(layer: &mut ChunkLayer) {
    for x in -PLATFORM_SIZE..=PLATFORM_SIZE {
        for z in -PLATFORM_SIZE..=PLATFORM_SIZE {
            let platform_pos = BlockPos::new(START_POS.x + x, START_POS.y, START_POS.z + z);
            layer.set_block(platform_pos, BlockState::MOSS_BLOCK);
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

fn visualize_array(array: &[i32], wall_offset: BlockPos, layer: &mut ChunkLayer) {
    // Clear previous visualization
    for x in 0..MAX_HEIGHT {
        for y in 0..ARRAY_SIZE {
            let pos = BlockPos::new(wall_offset.x + x, wall_offset.y + y, wall_offset.z);
            layer.set_block(pos, BlockState::AIR);
        }
    }

    // Create new visualization
    for (i, &value) in array.iter().enumerate() {
        let width = (value as f32 / ARRAY_SIZE as f32 * MAX_HEIGHT as f32) as i32;
        let block_type = get_block_color(value);

        for x in 0..width {
            let pos = BlockPos::new(
                wall_offset.x + x,
                wall_offset.y + (ARRAY_SIZE - 1 - i as i32) as i32, // Reversed y-axis so larger numbers appear at bottom
                wall_offset.z,
            );
            layer.set_block(pos, block_type);
        }
    }
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

        client.send_chat_message("Welcome to the Sorting Visualizer!".italic());

        let random_array = generate_random_array();
        let wall_offset =
            BlockPos::new(START_POS.x - ARRAY_SIZE / 2, START_POS.y, START_POS.z + 50);

        let state = VisualizerState {
            array: random_array,
            wall_offset,
        };

        let mut layer = ChunkLayer::new(ident!("overworld"), &dimensions, &biomes, &server);

        // Create platform and initial visualization
        create_platform(&mut layer);
        visualize_array(&state.array, wall_offset, &mut layer);

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

            // Reset platform and visualization
            create_platform(&mut layer);
            visualize_array(&state.array, state.wall_offset, &mut layer);

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

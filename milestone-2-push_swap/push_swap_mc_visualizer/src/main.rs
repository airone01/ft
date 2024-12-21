#![allow(clippy::type_complexity)]

pub mod chunks;
pub mod consts;
pub mod network;
pub mod push_swap;
pub mod utils;
pub mod visualizer;

use chunks::manage_chunks;
use consts::{ARRAY_SIZE, START_POS, VIEW_DIST};
use network::SortingVisualizerServer;
use utils::generate_random_array;
use visualizer::blocks::{create_backdrop, create_platform};

use valence::network::ConnectionMode;
use valence::prelude::*;
use valence::spawn::IsFlat;
use visualizer::{handle_click, visualize_array};

#[derive(Component)]
struct VisualizerState {
    array_a: Vec<i32>,
    array_b: Vec<i32>,
    wall_offset_a: BlockPos,
    wall_offset_b: BlockPos,
    last_click: f64,
    is_sorting: bool,
    pending_instructions: Option<Vec<String>>,
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

        client.send_chat_message(
            "=====================================================\n".color(Color::DARK_GRAY),
        );
        client.send_chat_message(
            "               Welcome to the push_swap Visualizer!".color(Color::GREEN),
        );
        client.send_chat_message(
            "\n=====================================================".color(Color::DARK_GRAY),
        );

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
            array_a: Vec::new(),
            array_b: Vec::new(),
            wall_offset_a,
            wall_offset_b,
            last_click: 0.0,
            pending_instructions: Some(Vec::new()),
            // last_instruction_time: 0.0,
            is_sorting: false,
            // last_click: 0.0,
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

pub fn main() {
    App::new()
        .insert_resource(NetworkSettings {
            connection_mode: ConnectionMode::Online {
                prevent_proxy_connections: false,
            },
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

#![allow(clippy::type_complexity)]

mod chunks;
mod cli;
mod consts;
mod network;
mod push_swap;
mod settings;
mod state;
mod utils;
mod visualizer;

use clap::Parser as _;
use log::info as pretty_info;

use crate::chunks::manage_chunks;
use crate::cli::Args;
use crate::consts::*;
use crate::network::SortingVisualizerServer;
use crate::settings::*;
use crate::state::*;
use crate::utils::rainbow_text;
use crate::visualizer::*;

use valence::interact_block::InteractBlockEvent;
use valence::log as _;
use valence::network::ConnectionMode;
use valence::prelude::*;
use valence::spawn::IsFlat;

#[macro_use]
extern crate log;

pub fn init_clients(
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
        info!("Initializing new client (entity: {:?})", entity);

        let settings = get_settings();
        visible_chunk_layer.0 = entity;
        is_flat.0 = true;
        *game_mode = GameMode::Creative;

        client.set_title("");
        client.set_subtitle(rainbow_text(
            "Welcome to this goofy ahh push_swap visualizer!",
        ));
        // client.send_chat_message();

        let wall_offset_a = BlockPos::new(
            START_POS.x + 50,
            START_POS.y - (settings.array_size as f32 * 0.5).floor() as i32,
            START_POS.z + 50,
        );
        let wall_offset_b = BlockPos::new(
            START_POS.x,
            START_POS.y - (settings.array_size as f32 * 0.5).floor() as i32,
            START_POS.z + 50,
        );

        debug!(
            "Creating initial state with wall offsets: {:?}, {:?}",
            wall_offset_a, wall_offset_b
        );

        let state = VisualizerState {
            array_a: Vec::new(),
            array_b: Vec::new(),
            wall_offset_a,
            wall_offset_b,
            last_click: 0.0,
            pending_instructions: Some(Vec::new()),
            is_sorting: false,
            last_status_check: std::time::SystemTime::now(),
            push_swap_status: PushSwapStatus::NotStarted,
            last_instruction_time: 0.0,
            current_instruction_index: 0,
        };

        let mut layer = ChunkLayer::new(ident!("overworld"), &dimensions, &biomes, &server);

        debug!("Creating initial visualization elements");
        create_platform(&mut layer);
        create_backdrop(state.wall_offset_a, state.wall_offset_b, &mut layer);
        visualize_array(&state.array_a, state.wall_offset_a, &mut layer);
        visualize_array(&state.array_b, state.wall_offset_b, &mut layer);

        info!("Client initialization complete, inserting components");
        commands.entity(entity).insert(state).insert(layer);
    }
}

pub fn reset_clients(
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
            info!("Resetting client state");

            // Init chunks
            debug!("Initializing chunks");
            for pos in ChunkView::new(START_POS.into(), VIEW_DIST).iter() {
                layer.insert_chunk(pos, UnloadedChunk::new());
            }

            // Reset platform, backdrop and visualization
            debug!("Resetting platform and visualization elements");
            create_platform(&mut layer);
            create_backdrop(state.wall_offset_a, state.wall_offset_b, &mut layer);
            visualize_array(&state.array_a, state.wall_offset_a, &mut layer);
            visualize_array(&state.array_b, state.wall_offset_b, &mut layer);

            // Position player for optimal viewing
            debug!("Setting player position and look direction");
            pos.set([
                f64::from(START_POS.x) + 0.5,
                f64::from(START_POS.y) + 1.0,
                f64::from(START_POS.z) + 0.5,
            ]);
            look.yaw = 0.0;
            look.pitch = 0.0;

            info!("Client reset complete");
        }
    }
}

#[tokio::main]
pub async fn main() {
    let args = Args::parse();
    init_settings(&args);

    let settings = get_settings();
    if settings.info {
        pretty_env_logger::init();

        pretty_info!("-------------- Executable info --------------");
        pretty_info!("Server version   : {}", env!("CARGO_PKG_VERSION"));
        pretty_info!(
            "Server build     : {}",
            option_env!("BUILD_HASH").unwrap_or("dev-build")
        );
        pretty_info!("--------------- Server config ---------------");
        pretty_info!("MAX_HEIGHT : {}", settings.max_height);
        pretty_info!("ARRAY_SIZE : {}", settings.array_size);
        pretty_info!("INSTR_DELAY: {}", settings.instr_delay);
        pretty_info!("VIEW_DIST  : {}", VIEW_DIST);
        pretty_info!("---------------------------------------------");
        return;
    }

    if let Err(e) = setup_executable() {
        println!("Error: {}", e);
        return;
    }

    let mut binding = App::new();
    let app = binding
        .insert_resource(NetworkSettings {
            connection_mode: ConnectionMode::Online {
                prevent_proxy_connections: false,
            },
            callbacks: SortingVisualizerServer.into(),
            ..Default::default()
        })
        .init_resource::<PushSwapChannel>()
        .init_resource::<RuntimeResource>()
        .add_plugins(DefaultPlugins)
        .add_event::<InteractBlockEvent>()
        .add_systems(
            Update,
            (
                init_clients,
                reset_clients.after(init_clients),
                manage_chunks.after(reset_clients),
                execute_initial_push_swap.after(init_clients),
                check_push_swap_status,
                process_instructions.after(check_push_swap_status),
                handle_click,
                despawn_disconnected_clients,
            ),
        );

    info!(
        "Server stared at {}",
        std::time::SystemTime::now()
            .duration_since(std::time::UNIX_EPOCH)
            .unwrap()
            .as_secs()
    );
    app.run();

    info!("Server terminated");
}

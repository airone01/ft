use crate::consts::MINECRAFT_VERSION;

use core::net::SocketAddr;

use valence::prelude::Uuid;
use valence::text::{Color, IntoText as _};
use valence::{
    network::{async_trait, HandshakeData, PlayerSampleEntry, ServerListPing},
    prelude::{NetworkCallbacks, SharedNetworkState},
};

pub struct SortingVisualizerServer;

#[async_trait]
impl NetworkCallbacks for SortingVisualizerServer {
    async fn server_list_ping(
        &self,
        _shared: &SharedNetworkState,
        _remote_addr: SocketAddr,
        handshake_data: &HandshakeData,
    ) -> ServerListPing {
        debug!("Received server list ping from {}", _remote_addr);
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
            favicon_png: include_bytes!("../../assets/logo-64x64.png"),
            version_name: ("Valence ".color(Color::GOLD) + MINECRAFT_VERSION.color(Color::RED))
                .to_legacy_lossy(),
            protocol: handshake_data.protocol_version,
        }
    }
}

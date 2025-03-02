#![allow(clippy::type_complexity)]

use valence::BlockPos;
use valence::BlockState;

pub use valence::MINECRAFT_VERSION;

pub const START_POS: BlockPos = BlockPos::new(0, 100, 0);
pub const VIEW_DIST: u8 = 10;
pub const PLATFORM_SIZE: i32 = 4;

// Different colored blocks for visualization
pub const VISUALIZATION_BLOCKS: [BlockState; 12] = [
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

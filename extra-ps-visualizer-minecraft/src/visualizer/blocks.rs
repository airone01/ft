use valence::{BlockPos, BlockState, ChunkLayer};

use crate::consts::*;
use crate::settings::get_settings;

/// Creates the backdrop wall
pub fn create_backdrop(wall_offset_a: BlockPos, wall_offset_b: BlockPos, layer: &mut ChunkLayer) {
    let settings = get_settings();

    // Calculate total dimensions - ensure we have enough space
    let total_width = (wall_offset_a.x - wall_offset_b.x) + settings.max_height + 4;
    let total_height = settings.array_size + 4;

    // Create black wall
    for x in 0..total_width {
        for y in 0..total_height {
            let pos = BlockPos::new(
                wall_offset_b.x - x + 2 + settings.max_height,
                wall_offset_b.y + y - 2,
                wall_offset_b.z + 1,
            );
            layer.set_block(pos, BlockState::BLACK_CONCRETE);
        }
    }
}

/// Creates the starting platform
pub fn create_platform(layer: &mut ChunkLayer) {
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

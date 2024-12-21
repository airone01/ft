use valence::{BlockPos, BlockState, ChunkLayer};

use crate::consts::{ARRAY_SIZE, MAX_HEIGHT, PLATFORM_SIZE, START_POS};

pub fn create_backdrop(wall_offset_a: BlockPos, wall_offset_b: BlockPos, layer: &mut ChunkLayer) {
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

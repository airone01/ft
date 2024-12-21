pub mod blocks;
mod handler;
pub mod utils;
pub use handler::handle_click;

use utils::get_block_color;
use valence::{BlockPos, BlockState, ChunkLayer};

use crate::consts::{ARRAY_SIZE, MAX_HEIGHT};

pub fn visualize_array(array: &[i32], wall_offset: BlockPos, layer: &mut ChunkLayer) {
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

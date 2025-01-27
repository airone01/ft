pub mod blocks;
mod handler;
pub mod utils;

pub use blocks::{create_backdrop, create_platform};
pub use handler::{handle_click, process_instructions};
pub use utils::get_block_color;

use crate::settings::get_settings;

use valence::{BlockPos, BlockState, ChunkLayer};

/// Visualizes the given array on the wall
pub fn visualize_array(array: &[i32], wall_offset: BlockPos, layer: &mut ChunkLayer) {
    let settings = get_settings();

    // Clear previous visualization
    for x in 0..settings.max_height {
        for y in 0..settings.array_size {
            let pos = BlockPos::new(wall_offset.x - x, wall_offset.y + y, wall_offset.z);
            layer.set_block(pos, BlockState::AIR);
        }
    }

    // Create new visualization
    for (i, &value) in array.iter().enumerate() {
        // Scale width based on the value's proportion of max_value
        // This ensures the largest number uses max_height blocks
        // and everything else scales proportionally
        let width = (value as f32 / settings.array_size as f32 * settings.max_height as f32) as i32;
        let block_type = get_block_color(value);

        for x in 0..width {
            // Change the y-coordinate calculation to start from the top
            let pos = BlockPos::new(
                wall_offset.x - x,
                wall_offset.y + (settings.array_size - 1 - i as i32),
                wall_offset.z,
            );
            layer.set_block(pos, block_type);
        }
    }
}

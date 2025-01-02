// src/visualizer/mod.rs
pub mod blocks;
mod handler;
pub mod utils;

pub use blocks::{create_backdrop, create_platform};
pub use handler::{handle_click, process_instructions};
pub use utils::get_block_color;

use valence::{BlockPos, BlockState, ChunkLayer};

use crate::settings::get_settings;

/// Visualizes the given array on the wall
///
/// # Arguments
///
/// * `array` - The array to visualize
/// * `wall_offset` - The position of the wall
/// * `layer` - The layer to draw the visualization on
///
/// # Example
///
/// ```
/// use valence::{BlockPos, BlockState, ChunkLayer};
/// use visualizer::visualize_array;
///
/// let array = [1, 2, 3, 4, 5];
/// let wall_offset = BlockPos::new(0, 0, 0);
/// let mut layer = ChunkLayer::new();
/// visualize_array(&array, wall_offset, &mut layer);
/// ```
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
        let width = (value as f32 / settings.array_size as f32 * settings.max_height as f32) as i32;
        let block_type = get_block_color(value);

        for x in 0..width {
            // Change the y-coordinate calculation to start from the top
            let pos = BlockPos::new(
                wall_offset.x - x,
                wall_offset.y + (settings.array_size - 1 - i as i32), // This is the key change
                wall_offset.z,
            );
            layer.set_block(pos, block_type);
        }
    }
}

#[cfg(test)]
mod visualizer_tests {
    use crate::{get_block_color, utils::initialize_test};
    use valence::BlockState;

    #[test]
    fn test_get_block_color() {
        initialize_test();

        // Test minimum value
        let min_color = get_block_color(1);
        assert_eq!(min_color, BlockState::RED_WOOL);

        // Test maximum value
        let max_color = get_block_color(50);
        assert_eq!(max_color, BlockState::BLUE_WOOL);
    }
}

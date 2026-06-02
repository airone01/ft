use valence::BlockState;

use crate::consts::VISUALIZATION_BLOCKS;
use crate::settings::get_settings;

/// Get the color of a block based on its value
///
/// ## Arguments
///
/// * `value` - The value of the block
///
/// ## Example
///
/// ```
/// use crate::visualizer::get_block_color;
/// use valence::BlockState;
///
/// let block_color = get_block_color(50);
/// assert_eq!(block_color, BlockState::PURPLE_WOOL);
/// ```
pub fn get_block_color(value: i32) -> BlockState {
    // Map value to color based on its magnitude
    let index = ((value as f32 / get_settings().array_size as f32)
        * (VISUALIZATION_BLOCKS.len() - 1) as f32) as usize;
    VISUALIZATION_BLOCKS[index]
}

#[cfg(test)]
mod tests {
    use crate::{get_block_color, utils::initialize_test, VISUALIZATION_BLOCKS};
    use valence::BlockState;

    #[test]
    fn test_get_block_color_min_value() {
        initialize_test();

        assert_eq!(get_block_color(1), BlockState::RED_WOOL);
    }

    #[test]
    fn test_get_block_color_max_value() {
        initialize_test();

        assert_eq!(get_block_color(50), BlockState::BLUE_WOOL);
    }

    #[test]
    fn test_get_block_color_mid_value() {
        initialize_test();

        assert_eq!(get_block_color(25), BlockState::YELLOW_CONCRETE);
    }

    #[test]
    fn test_get_block_color_quarter_value() {
        initialize_test();

        assert_eq!(get_block_color(12), BlockState::ORANGE_CONCRETE);
    }

    #[test]
    fn test_get_block_color_three_quarters_value() {
        initialize_test();

        assert_eq!(get_block_color(37), BlockState::GREEN_CONCRETE_POWDER);
    }

    #[test]
    fn test_get_block_color_sequence() {
        initialize_test();

        let mut last_index = 0;
        for i in (1..=50).step_by(10) {
            let block = get_block_color(i);
            let current_index = VISUALIZATION_BLOCKS
                .iter()
                .position(|&b| b == block)
                .unwrap();
            if i > 1 {
                assert!(current_index >= last_index);
            }
            last_index = current_index;
        }
    }
}

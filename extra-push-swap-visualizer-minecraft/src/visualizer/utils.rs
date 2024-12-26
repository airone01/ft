use valence::BlockState;

use crate::{consts::VISUALIZATION_BLOCKS, get_settings};

pub fn get_block_color(value: i32) -> BlockState {
    // Map value to color based on its magnitude
    let index = ((value as f32 / get_settings().array_size as f32)
        * (VISUALIZATION_BLOCKS.len() - 1) as f32) as usize;
    VISUALIZATION_BLOCKS[index]
}

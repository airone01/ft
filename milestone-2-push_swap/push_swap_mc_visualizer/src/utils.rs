use crate::consts::ARRAY_SIZE;

use valence::prelude::Color;
use valence::prelude::IntoText as _;
use valence::Text;

pub fn generate_random_array() -> Vec<i32> {
    let mut array = Vec::with_capacity(ARRAY_SIZE as usize);
    for i in 0..ARRAY_SIZE {
        array.push(i + 1);
    }
    use rand::seq::SliceRandom;
    let mut rng = rand::thread_rng();
    array.shuffle(&mut rng);
    array
}

/// Creates a rainbow effect by coloring each character with a gradually shifting hue
pub fn rainbow_text(text: &str) -> Text {
    let char_count = text.chars().count();
    if char_count == 0 {
        return Text::default();
    }

    // Start with an empty Text
    let mut result = Text::default();

    // Add each character with its rainbow color
    for (i, c) in text.chars().enumerate() {
        // Calculate hue for this character (0 to 360 degrees)
        let hue = (i as f32 / char_count as f32) * 360.0;

        // Convert HSV to RGB (assuming saturation and value are 1.0)
        let (r, g, b) = hsv_to_rgb(hue, 1.0, 1.0);

        // Convert single character to Text with color and append it
        result = result + c.to_string().color(Color::rgb(r, g, b));
    }

    result
}

/// Converts HSV color values to RGB
/// hue: 0-360 degrees
/// saturation: 0.0-1.0
/// value: 0.0-1.0
/// Returns: (r, g, b) as u8 values (0-255)
fn hsv_to_rgb(hue: f32, saturation: f32, value: f32) -> (u8, u8, u8) {
    let c = value * saturation;
    let h = hue / 60.0;
    let x = c * (1.0 - (h % 2.0 - 1.0).abs());
    let m = value - c;

    let (r, g, b) = match h as i32 {
        0..=0 => (c, x, 0.0),
        1..=1 => (x, c, 0.0),
        2..=2 => (0.0, c, x),
        3..=3 => (0.0, x, c),
        4..=4 => (x, 0.0, c),
        5..=5 => (c, 0.0, x),
        _ => (0.0, 0.0, 0.0),
    };

    (
        ((r + m) * 255.0) as u8,
        ((g + m) * 255.0) as u8,
        ((b + m) * 255.0) as u8,
    )
}

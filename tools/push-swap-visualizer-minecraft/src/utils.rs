use std::sync::Once;

use valence::prelude::Color;
use valence::prelude::IntoText as _;
use valence::Text;

use crate::settings::get_settings;

/// Generates a random array of integers from 1 to the array size
/// The array is shuffled to ensure randomness
///
/// Returns: Vec<i32> of random integers
pub fn generate_random_array() -> Vec<i32> {
    let settings = get_settings();
    let mut array = Vec::with_capacity(settings.array_size as usize);
    for i in 0..settings.array_size {
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

#[allow(dead_code)]
static INIT: Once = Once::new();

#[allow(dead_code)]
pub fn initialize_test() {
    INIT.call_once(|| {
        let args = crate::cli::Args {
            executable: "test_exec".to_string(),
            makefile: "test_make".to_string(),
            info: true,
            cwd: "/test/path".to_string(),
            array_size: 50,
            instr_delay: 0.1,
            max_height: 75,
        };
        crate::settings::init_settings(&args);
    });
}

#[cfg(test)]
mod utils_tests {
    use valence::Text;

    use crate::utils::{generate_random_array, hsv_to_rgb, initialize_test, rainbow_text};

    #[test]
    fn test_generate_random_array_size() {
        initialize_test();

        let array = generate_random_array();
        assert_eq!(array.len(), 50);
    }

    #[test]
    fn test_generate_random_array_uniqueness() {
        initialize_test();

        let array = generate_random_array();
        let mut unique_numbers: Vec<i32> = array.clone();
        unique_numbers.sort();
        unique_numbers.dedup();

        assert_eq!(unique_numbers.len(), array.len());
    }

    #[test]
    fn test_generate_random_array_range() {
        initialize_test();

        let array = generate_random_array();
        assert!(array.iter().all(|&x| x >= 1 && x <= 50));
    }
    #[test]
    fn test_rainbow_text_empty() {
        let result = rainbow_text("");
        assert_eq!(result, Text::default());
    }

    #[test]
    fn test_rainbow_text_single_char() {
        let result = rainbow_text("a");
        assert!(!result.to_string().is_empty());
    }

    #[test]
    fn test_rainbow_text_multiple_chars() {
        let text = "Hello";
        let result = rainbow_text(text);
        assert!(result.to_string().len() > text.len());
    }

    #[test]
    fn test_hsv_to_rgb_red() {
        let (r, g, b) = hsv_to_rgb(0.0, 1.0, 1.0);
        assert_eq!((r, g, b), (255, 0, 0));
    }

    #[test]
    fn test_hsv_to_rgb_green() {
        let (r, g, b) = hsv_to_rgb(120.0, 1.0, 1.0);
        assert_eq!((r, g, b), (0, 255, 0));
    }

    #[test]
    fn test_hsv_to_rgb_blue() {
        let (r, g, b) = hsv_to_rgb(240.0, 1.0, 1.0);
        assert_eq!((r, g, b), (0, 0, 255));
    }

    #[test]
    fn test_hsv_to_rgb_black() {
        let (r, g, b) = hsv_to_rgb(0.0, 0.0, 0.0);
        assert_eq!((r, g, b), (0, 0, 0));
    }

    #[test]
    fn test_hsv_to_rgb_white() {
        let (r, g, b) = hsv_to_rgb(0.0, 0.0, 1.0);
        assert_eq!((r, g, b), (255, 255, 255));
    }
}

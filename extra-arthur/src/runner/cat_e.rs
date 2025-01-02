use crossterm::style::Stylize;

pub trait CatE {
    fn cat_e(&self) -> String;
    fn debug_display(&self) -> String;
}

impl CatE for String {
    fn cat_e(&self) -> String {
        let mut result = String::with_capacity(self.len() * 2);

        for byte in self.bytes() {
            match byte {
                0..=31 => {
                    if byte == b'\n' {
                        result.push_str("$\n");
                    } else {
                        result.push('^');
                        result.push((byte + 64) as char);
                    }
                }
                127 => result.push_str("^?"),
                128..=159 => {
                    result.push_str("M-^");
                    result.push((byte - 64) as char);
                }
                160..=255 => {
                    result.push_str("M-");
                    result.push((byte - 128) as char);
                }
                _ => result.push(byte as char),
            }
        }

        result
    }

    fn debug_display(&self) -> String {
        self.cat_e().black().on_yellow().bold().to_string()
    }
}

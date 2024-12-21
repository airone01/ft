use crate::consts::ARRAY_SIZE;

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

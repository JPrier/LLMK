use keyboard_core::MatrixHardware;

pub struct MockMatrix {
    pub rows: Vec<u16>,
}

impl MatrixHardware for MockMatrix {
    fn read_row(&self, row: usize) -> u16 {
        self.rows[row]
    }
}

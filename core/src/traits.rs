pub trait MatrixHardware {
    fn read_row(&self, row: usize) -> u16;
}

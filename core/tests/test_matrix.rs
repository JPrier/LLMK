use keyboard_core::MatrixHardware;
mod mock_matrix;
use mock_matrix::MockMatrix;

#[test]
fn read_row_returns_correct_value() {
    let mock = MockMatrix {
        rows: vec![0b1100u16, 0b0011u16],
    };
    assert_eq!(mock.read_row(0), 0b1100u16);
    assert_eq!(mock.read_row(1), 0b0011u16);
}

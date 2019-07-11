#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix final {
private:
	int m_rows = 0;
	int m_cols = 0;

	std::vector<std::vector<int>> m_matrix {};

private:
	void init(int rows, int cols) {
		if (rows < 0 || cols < 0) {
			throw std::out_of_range { "" };
		}//fi

		m_rows = cols == 0 ? 0 : rows;
		m_cols = rows == 0 ? 0 : cols;

		m_matrix.clear();
		m_matrix.resize(rows);

		for (auto& m : m_matrix) {
			m.resize(cols);
		}//rof
	}

public:
	Matrix() : Matrix(0, 0) {}
	Matrix(int rows, int cols) {
		init(rows, cols);
	}

	Matrix operator+(const Matrix& rhs) const {
		if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
			throw std::invalid_argument { "" };
		}//fi

		Matrix matrix { m_rows, m_cols };

		for (int row = 0; row < m_rows; ++row) {
			for (int col = 0; col < m_cols; ++col) {
				matrix.At(row, col) = At(row, col) + rhs.At(row, col);
			}//rof
		}//rof

		return matrix;
	}

	bool operator==(const Matrix& rhs) const {
		if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
			return false;
		}//fi

		for (int row = 0; row < m_rows; ++row) {
			for (int col = 0; col < m_cols; ++col) {
				if (At(row, col) != rhs.At(row, col)) {
					return false;
				}//fi
			}//rof
		}//rof

		return true;
	}

	friend std::ostream& operator<<(std::ostream& lhs, const Matrix& rhs) {
		lhs << rhs.m_rows << " " << rhs.m_cols << std::endl;

		for (int row = 0; row < rhs.m_rows; ++row) {
			for (int col = 0; col < rhs.m_cols; ++col) {
				lhs << rhs.At(row, col) << " ";
			}//rof

			lhs << std::endl;
		}//rof

		return lhs;
	}

	friend std::istream& operator>>(std::istream& lhs, Matrix& rhs) {
		int rows = 0, cols = 0;
		lhs >> rows >> cols;
		rhs.Reset(rows, cols);

		for (int row = 0; row < rhs.m_rows; ++row) {
			for (int col = 0; col < rhs.m_cols; ++col) {
				lhs >> rhs.At(row, col);
			}//rof
		}//rof

		return lhs;
	}

public:
	void Reset(int rows, int cols) {
		init(rows, cols);
	}

	int At(int row, int col) const {
		return m_matrix.at(row).at(col);
	}

	int& At(int row, int col) {
		return m_matrix.at(row).at(col);
	}

	int GetNumRows() const { return m_rows; };
	int GetNumColumns() const { return m_cols; };
};

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;

	return 0;
}

#ifndef YK_37039987_MATRIX_H
#define YK_37039987_MATRIX_H
#include <vector>

template <typename T>
class Matrix
{
public:
	Matrix() : Matrix{ 0, 0 } {}

	Matrix(int rows, int cols) : grid{ rows } {
		for (auto & thisRow : grid) thisRow.resize(cols);
	}

	Matrix(std::vector<std::vector<T>> v) : grid{ v } {}

	Matrix(std::vector<std::vector<T>>&& v) : grid{ std::move(v) } {}

	const std::vector<T>& operator[](int row) const { return grid[row]; }

	std::vector<T>& operator[](int row) { return grid[row]; }

	int numRows() const { return grid.size(); }

	int numCols() const {
		return (numRows() > 0) ? grid[0].size() : 0;
	}

	void resize(int newNumRows, int newNumCols) {
		if (newNumRows >= numRows() && newNumCols >= numCols()) {
			grid.resize(newNumRows);
			for (auto & thisRow : grid) thisRow.resize(newNumCols);
		}
	}

private:
	std::vector<std::vector<T>> grid;
};
#endif

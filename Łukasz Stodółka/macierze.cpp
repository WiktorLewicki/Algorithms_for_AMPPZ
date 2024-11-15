#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    vector<vector<double>> data;
    int rows, cols;

    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows, vector<double>(cols, 0));
    }

    Matrix(const vector<vector<double>> &values)
        : data(values), rows(values.size()), cols(values[0].size()) {}

    Matrix operator+(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for addition.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for subtraction.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix &other) const {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions are incompatible for multiplication.");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    double determinant() const {
        if (rows != cols) {
            throw invalid_argument("Determinant is only defined for square matrices.");
        }
        Matrix temp = *this;
        return gaussianEliminationDeterminant(temp);
    }
	
	Matrix operator,(int power) const {
        if (rows != cols) {
            throw invalid_argument("Exponentiation is only defined for square matrices.");
        }
        Matrix result = identity(rows);
        Matrix base = *this;

        while (power > 0) {
            if (power % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            power /= 2;
        }

        return result;
    }

    friend ostream& operator<<(ostream &os, const Matrix &matrix) {
        for (const auto &row : matrix.data) {
            for (double elem : row) {
                os << elem << " ";
            }
            os << endl;
        }
        return os;
    }


	 
private:
    double gaussianEliminationDeterminant(Matrix &matrix) const {
        int n = matrix.rows;
        double det = 1;
        for (int i = 0; i < n; ++i) {
            int pivot = i;
            for (int j = i + 1; j < n; ++j) {
                if (abs(matrix.data[j][i]) > abs(matrix.data[pivot][i])) {
                    pivot = j;
                }
            }
            if (abs(matrix.data[pivot][i]) < 1e-9) {
                return 0;
            }
            if (pivot != i) {
                swap(matrix.data[i], matrix.data[pivot]);
                det = -det;
            }
            det *= matrix.data[i][i];
            for (int j = i + 1; j < n; ++j) {
                double factor = matrix.data[j][i] / matrix.data[i][i];
                for (int k = i; k < n; ++k) {
                    matrix.data[j][k] -= factor * matrix.data[i][k];
                }
            }
        }
        return det;
    }

	static Matrix identity(int size) {
        Matrix id(size, size);
        for (int i = 0; i < size; ++i) {
            id.data[i][i] = 1;
        }
        return id;
    }
};

int main() {
    vector<vector<double>> mat1_values = {{1, 1}, {1, 0}};
    vector<vector<double>> mat2_values = {{5, 6}, {7, 8}};

    Matrix mat1(mat1_values);
    Matrix mat2(mat2_values);

	cout << (mat1,(4));
    return 0;
}


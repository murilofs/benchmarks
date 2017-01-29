#include <complex>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "cowichan.h"

namespace cowichan {

    std::vector<std::vector<int>> mandel(int nrows, int ncols, float x0, float y0, float dx, float dy) {
        const int iterations = 150;
        std::vector<std::vector<int>> matrix(nrows, std::vector<int>(ncols));

        std::complex<float> z;
        std::complex<float> c;

        for (int i = 0; i < ncols; i++) {
            for (int j = 0; j < nrows; j++) {
                c = std::complex<float>(x0 + (dx / ncols) * i, (dy + y0) - (dy / nrows) * j);
                z = std::complex<float>(0.0f, 0.0f);
                int iter = 0;

                while ((std::abs(z) < 2) && (iter < iterations)) {
                    z = z * z + c;
                    iter++;
                }

                matrix[j][i] = iter;
            }
        }

        return matrix;
    }

    std::vector<std::vector<int>> randmat(int nrows, int ncols, int s) {
        std::vector<std::vector<int>> matrix(nrows, std::vector<int>(ncols));
        srand(s);

        for (int i = 0; i < ncols; i++) {
            for (int j = 0; j < nrows; j++) {
                matrix[i][j] = rand();
            }
        }

        return matrix;
    }

    std::vector<std::vector<int>> shuffle(std::vector<std::vector<int>> matrix) {
        std::vector<std::vector<int>> shuffled_matrix(matrix.size());

        for (auto matrix_rows : matrix) {
            for (auto matrix_value : matrix_rows) {
                std::cout << matrix_value << " ";
            }
            std::cout << std::endl;
        }

        return matrix;
    }

    std::vector<std::vector<bool>> invperc(int *matrix, int nfill) {

    }

    std::vector<std::vector<bool>> thresh(std::vector<std::vector<int>> matrix, int percent) {

    }
}
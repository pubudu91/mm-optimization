//
// Created by root on 10/8/16.
//

#include <iostream>
#include "Matrix.h"
#include "../utils/MiscOps.h"

using namespace std;

Matrix::Matrix(const unsigned int n) : size(n) {
    matrix = create2DArray(n);
}

void Matrix::printMatrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            cout << matrix[i][j] << " ";

        cout << endl;
    }
    cout << endl;
}

void Matrix::fillMatrix() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            matrix[i][j] = randomDouble();
}


Matrix::~Matrix() {
    for (int i = 0; i < size; ++i)
        delete[] matrix[i];

    delete[] matrix;
}


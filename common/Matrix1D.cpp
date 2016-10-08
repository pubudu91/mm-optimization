//
// Created by pubudu on 10/6/16.
//

#include <iostream>
#include "Matrix1D.h"
#include "../utils/MiscOps.h"

using namespace std;

Matrix1D::Matrix1D(const unsigned int size) : size(size) {
    matrix = new double[size * size];
}

void Matrix1D::printMatrix() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            cout << matrix[i * size + j] << " ";

        cout << endl;
    }

    cout << endl;
}

void Matrix1D::fillMatrix() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            matrix[i * size + j] = randomDouble();
}


Matrix1D::~Matrix1D() {
    delete[] matrix;
}


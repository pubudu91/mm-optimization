//
// Created by pubudu on 10/6/16.
//

#include <chrono>
#include <omp.h>
#include "MatrixOps.h"

using namespace std;

void multiply(Matrix *A, Matrix *B, Matrix *C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C->matrix[i][j] += A->matrix[i][k] * B->matrix[j][k];
}


void multiply1D(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    for (int i = 0; i < n; ++i) {
        double *Arow = &A->matrix[i * n];
        double *Crow = &C->matrix[i * n];
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < n; ++k)
                sum += *(Arow + k) * B->matrix[k * n + j];

            *(Crow + j) = sum;
        }
    }
}

void parallelMultiply(Matrix *A, Matrix *B, Matrix *C, int n) {
    omp_set_num_threads(4);

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }
}

void parallelMultiply1D(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    omp_set_num_threads(4);

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        double *Arow = &A->matrix[i * n];
        double *Crow = &C->matrix[i * n];
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < n; ++k)
                sum += *(Arow + k) * B->matrix[k * n + j];

            *(Crow + j) = sum;
        }
    }
}





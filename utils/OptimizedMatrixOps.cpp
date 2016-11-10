//
// Created by pubudu on 10/6/16.
//

#include <omp.h>
#include <cblas.h>
#include <chrono>
#include "OptimizedMatrixOps.h"
#include "MiscOps.h"

using namespace std;

void transposedParallelMultiply(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    B = transpose1D(B, n);

    omp_set_num_threads(4);

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        double *Arow = &A->matrix[i * n];
        double *Crow = &C->matrix[i * n];

        for (int j = 0; j < n; ++j) {
            double sum = 0;
            double *Brow = &B->matrix[j * n];

            for (int k = 0; k < n; ++k)
                sum += *(Arow + k) * *(Brow + k);

            *(Crow + j) = sum;
        }
    }
}

void multiply1DMatrixIKJ(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    for (int i = 0; i < n; ++i) {
        double *Arow = &A->matrix[i * n];
        double *Crow = &C->matrix[i * n];

        for (int k = 0; k < n; ++k) {
            double temp = *(Arow + k);
            double *Brow = &B->matrix[k * n];

            for (int j = 0; j < n; ++j)
                *(Crow + j) += temp * *(Brow + j);
        }
    }
}

void parallelMultiply1DMatrixIKJ(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    omp_set_num_threads(10);

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        double *Arow = &A->matrix[i * n];
        double *Crow = &C->matrix[i * n];

        for (int k = 0; k < n; ++k) {
            double temp = *(Arow + k);
            double *Brow = &B->matrix[k * n];

            for (int j = 0; j < n; ++j)
                *(Crow + j) += temp * *(Brow + j);
        }
    }
}

void blasL3(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, A->matrix, n, B->matrix, n, 0, C->matrix, n);
}

void blasL1(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    double *Cmat = C->matrix;
    double *Amat = A->matrix;
    double *Bmat = B->matrix;

    double *Arv, *Crv;

    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        Arv = Amat + i * n;
        Crv = Cmat + i * n;

        for (int j = 0; j < n; j++)
            *(Crv + j) = cblas_ddot(n, Arv, 1, &Bmat[j * n], 1);
    }
}

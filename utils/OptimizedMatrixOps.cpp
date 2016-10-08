//
// Created by pubudu on 10/6/16.
//

#include <omp.h>
#include <cblas.h>
#include <chrono>
#include "OptimizedMatrixOps.h"
#include "MiscOps.h"
#include "MatrixOps.h"

using namespace std;

void multiplyIKJ(Matrix *A, Matrix *B, Matrix *C, int n) {
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < n; ++j)
                C->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
}

void multiply1DMatrixIKJ(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < n; ++j)
                C->matrix[i * n + j] += A->matrix[i * n + k] * B->matrix[k * n + j];
}

void parallelMultiplyIKJ(Matrix *A, Matrix *B, Matrix *C, int n) {
    omp_set_num_threads(10);

//    int i, j, k;

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < n; ++j)
                C->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
    }
}

void parallelMultiply1DMatrixIKJ(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    omp_set_num_threads(10);

    int i, j, k;

#pragma omp parallel for
    for (i = 0; i < n; ++i) {
        for (k = 0; k < n; ++k)
            for (j = 0; j < n; ++j)
                C->matrix[i * n + j] += A->matrix[i * n + k] * B->matrix[k * n + j];
    }
}

void blasL3(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, A->matrix, n, B->matrix, n, 0, C->matrix, n);
}

//double getTimeForOptimizedMultiplication(int n, bool is1Dop, MATRIX_OP op) {
//    if (is1Dop)
//        return timeFor1DMatrices(n, op);
//
//    Matrix *A = new Matrix(n);
//    Matrix *B = new Matrix(n);
//    Matrix *C = new Matrix(n);
//
//    A->fillMatrix();
//    B->fillMatrix();
//
//    auto begin = chrono::high_resolution_clock::now();
//    auto end = begin;
//
//    switch (op) {
//        case MultiplyIKJ:
//            begin = chrono::high_resolution_clock::now();
//            multiplyIKJ(A, B, C, n);
//            end = chrono::high_resolution_clock::now();
//            break;
//        case ParallelMultiplyIKJ:
//            begin = chrono::high_resolution_clock::now();
//            parallelMultiplyIKJ(A, B, C, n);
//            end = chrono::high_resolution_clock::now();
//            break;
//        case BLASL1:
//            B = transpose(B, n);
//            begin = chrono::high_resolution_clock::now();
//            blas1(A, B, C, n);
//            end = chrono::high_resolution_clock::now();
//            break;
//    }
//
////    auto end = chrono::high_resolution_clock::now();
//    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
//
//    delete A, B, C;
//
//    return duration / 1000000.0;
//}

void blas1(Matrix *A, Matrix *B, Matrix *C, int n) {
    double **Cmat = C->matrix;

    omp_set_num_threads(4);
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        double *Crow = Cmat[i];
        for (int j = 0; j < n; j++) {
            Crow[j] = cblas_ddot(n, A->matrix[i], 1, B->matrix[j], 1);
        }
    }
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

        for (int j = 0; j < n; j++) {
            *(Crv + j) = cblas_ddot(n, Arv, 1, &Bmat[j * n], 1);
        }
    }
}

//double timeFor1DMatrices(int n, MATRIX_OP op) {
//    Matrix1D *A = new Matrix1D(n);
//    Matrix1D *B = new Matrix1D(n);
//    Matrix1D *C = new Matrix1D(n);
//
//    A->fillMatrix();
//    B->fillMatrix();
//
//    auto begin = chrono::high_resolution_clock::now();
//    auto end = begin;
//
//    switch (op) {
//        case Multiply1DMatrixIKJ:
//            begin = chrono::high_resolution_clock::now();
//            multiply1DMatrixIKJ(A, B, C, n);
//            end = chrono::high_resolution_clock::now();
//            break;
//        case ParallelMultiply1DMatrixIKJ:
//            begin = chrono::high_resolution_clock::now();
//            parallelMultiply1DMatrixIKJ(A, B, C, n);
//            end = chrono::high_resolution_clock::now();
//            break;
//        case BLAS:
//            begin = chrono::high_resolution_clock::now();
//            blasL3(A, B, C, n);
//            end = chrono::high_resolution_clock::now();
//            break;
//        case BLASL1:
//            B = transpose1D(B, n);
//            begin = chrono::high_resolution_clock::now();
//            blasL1(A, B, C, n);
//            end = chrono::high_resolution_clock::now();
//            break;
//    }
//
//    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
//
//    delete A, B, C;
//
//    return duration / 1000000.0;
//}
//

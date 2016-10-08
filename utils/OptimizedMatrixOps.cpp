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

//void blas1(Matrix *A, Matrix *B, Matrix *C, int n) {
//    double **Cmat = C->matrix;
//
//    omp_set_num_threads(4);
//#pragma omp parallel for
//    for (int i = 0; i < n; ++i) {
//        double *Crow = Cmat[i];
//        for (int j = 0; j < n; j++) {
//            Crow[j] = cblas_ddot(n, A->matrix[i], 1, B->matrix[j], 1);
//        }
//    }
//}

void blasL1(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n) {
    double *Cmat = C->matrix;
    double *Amat = A->matrix;
    double *Bmat = B->matrix;

    double *Arv, *Crv;

    omp_set_num_threads(2);
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        Arv = Amat + i * n;
        Crv = Cmat + i * n;

        for (int j = 0; j < n; j++)
            *(Crv + j) = cblas_ddot(n, Arv, 1, &Bmat[j * n], 1);
    }
}

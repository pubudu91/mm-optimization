//
// Created by pubudu on 10/6/16.
//

#include "../common/Matrix.h"
#include "../common/Matrix1D.h"

#ifndef LAB4_5_OPTIMIZEDMATRIXOPS_H
#define LAB4_5_OPTIMIZEDMATRIXOPS_H

void multiplyIKJ(Matrix *A, Matrix *B, Matrix *C, int n);

void multiply1DMatrixIKJ(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n);

void parallelMultiplyIKJ(Matrix *A, Matrix *B, Matrix *C, int n);

void parallelMultiply1DMatrixIKJ(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n);

void blasL3(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n);

//void blas1(Matrix *A, Matrix *B, Matrix *C, int n);

void blasL1(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n);

#endif //LAB4_5_OPTIMIZEDMATRIXOPS_H


//
// Created by pubudu on 10/6/16.
//

#include "../common/Matrix.h"
#include "../common/Matrix1D.h"

#ifndef LAB4_5_MATRIXOPS_H
#define LAB4_5_MATRIXOPS_H

void multiply(Matrix *A, Matrix *B, Matrix *C, int n);

void multiply1D(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n);

void parallelMultiply(Matrix *A, Matrix *B, Matrix *C, int n);

void parallelMultiply1D(Matrix1D *A, Matrix1D *B, Matrix1D *C, int n);

#endif //LAB4_5_MATRIXOPS_H


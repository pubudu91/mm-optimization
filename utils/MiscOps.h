//
// Created by pubudu on 10/6/16.
//

#include "OptimizedMatrixOps.h"

#ifndef LAB4_5_MISCOPS_H
#define LAB4_5_MISCOPS_H

double average(double data[], int n);

double **create2DArray(int n);

void fillMatrix(double **mat, int size);

double randomDouble();

void fill1DArray(double *mat, int n);

void printMatrix(double *mat, int n);

int sampleSize(int n, bool is1Dop, MATRIX_OP op);

double standardDeviation(double data[], int n);

Matrix *transpose(Matrix *mat, int n);

Matrix1D *transpose1D(Matrix1D *mat, int n);

#endif //LAB4_5_MISCOPS_H


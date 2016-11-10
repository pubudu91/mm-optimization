//
// Created by pubudu on 10/6/16.
//

#include "OptimizedMatrixOps.h"

#ifndef LAB4_5_MISCOPS_H
#define LAB4_5_MISCOPS_H

double average(double data[], int n);

double randomDouble();

int sampleSize(int n, int version, int op);

double standardDeviation(double data[], int n);

Matrix1D *transpose1D(Matrix1D *mat, int n);

#endif //LAB4_5_MISCOPS_H


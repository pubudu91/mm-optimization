//
// Created by pubudu on 10/6/16.
//

#include <iostream>
#include <cmath>
#include "MiscOps.h"
#include "../common/Matrix.h"
#include "MatrixOps.h"
#include "../version1/version1.h"
#include "../version2/version2.h"

using namespace std;

double average(double data[], int n) {
    double total = 0;

    for (int i = 0; i < n; i++)
        total += data[i];

    double average = total / n;
    return average;
}

double **create2DArray(int n) {
    double **arr = new double *[n];

    for (int i = 0; i < n; ++i)
        arr[i] = new double[n]();

    return arr;
}

void fillMatrix(double **mat, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            mat[i][j] = randomDouble();
        }
    }
}

double randomDouble() {
    double max = 10000, min = -10000;
    double r = (double) rand() / RAND_MAX;
    return min + r * (max - min);
}

void fill1DArray(double *mat, int n) {
    for (int i = 0; i < n * n; ++i) {
        mat[i] = randomDouble();
    }
}

void printMatrix(double *mat, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << mat[i * n + j] << " ";
        }
        cout << endl;
    }
}

int sampleSize(int n, bool is1Dop, MATRIX_OP op) {
    double durations[20];
    double avg, std, base;

//    switch (op) {
//        case Sequential:
//            for (int i = 0; i < 20; ++i)
//                durations[i] = getTimeForMultiplication(n);
//            break;
//        case Parallel:
//            for (int i = 0; i < 20; ++i)
//                durations[i] = getTimeForParallelMultiplication(n);
//            break;
//        default:
//            for (int i = 0; i < 20; ++i)
//                durations[i] = getTimeForOptimizedMultiplication(n, is1Dop, op);
//            break;
//    }

    avg = average(durations, 20);
    std = standardDeviation(durations, 20);
    base = (100 * 1.96 * std) / (5 * avg);

    return (int) ceil(pow(base, 2));
}

double standardDeviation(double data[], int n) {
    double mean = 0.0, sum_deviation = 0.0;

    for (int i = 0; i < n; ++i)
        mean += data[i];

    mean = mean / n;
    for (int i = 0; i < n; ++i)
        sum_deviation += (data[i] - mean) * (data[i] - mean);

    return sqrt(sum_deviation / (n - 1));
}

Matrix *transpose(Matrix *mat, int n) {
    Matrix *temp = new Matrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            temp->matrix[i][j] = mat->matrix[j][i];
        }
    }
    return temp;
}

Matrix1D *transpose1D(Matrix1D *mat, int n) {
    Matrix1D *temp = new Matrix1D(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            temp->matrix[i * n + j] = mat->matrix[j * n + i];
        }
    }
    return temp;
}



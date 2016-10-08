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
#include "../version3/version3.h"

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

double randomDouble() {
    double max = 10000, min = -10000;
    double r = (double) rand() / RAND_MAX;
    return min + r * (max - min);
}

int sampleSize(int n, int version, int op) {
    int iterations = 15;
    double durations[iterations];
    double avg, std, base;

    switch (version) {
        case 1:
            for (int i = 0; i < iterations; ++i)
                durations[i] = getTimeForMultiplication(n);
            break;
        case 2:
            for (int i = 0; i < iterations; ++i)
                durations[i] = getTimeForParallelMultiplication(n);
            break;
        case 3:
            switch (op) {
                case 1:
                    for (int j = 0; j < iterations; ++j)
                        durations[j] = getTimeForIKJSeq(n);
                    break;
                case 2:
                    for (int i = 0; i < iterations; ++i)
                        durations[i] = getTimeForIKJParallel(n);
                    break;
                case 3:
                    for (int i = 0; i < iterations; ++i)
                        durations[i] = getTimeForBLASL1(n);
                    break;
                default:
                    for (int i = 0; i < iterations; ++i)
                        durations[i] = getTimeForBLASL3(n);
                    break;
            }
            break;
    }

    avg = average(durations, iterations);
    std = standardDeviation(durations, iterations);
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



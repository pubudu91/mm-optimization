//
// Created by root on 10/8/16.
//

#include <iostream>
#include <chrono>
#include "version2.h"
#include "../utils/MatrixOps.h"
#include "../utils/MiscOps.h"

using namespace std;

void runVersion2() {
    int iterations[] = {46, 31, 5, 4, 3, 2, 5, 3, 3, 3};
    double *durations, avg;
    int n = 0;

    cout << "=========== Running Version 2 ===========" << endl;

    for (int i = 0; i < 10; ++i) {
        n += 100;
        durations = new double[iterations[i]];

        for (int j = 0; j < iterations[i]; ++j)
            durations[j] = getTimeForParallelMultiplication(n);

        avg = average(durations, iterations[i]);

        cout << "For parallel n = " << n << " , average time = " << avg << " ms" << endl;

        delete[] durations;
    }
}

double getTimeForParallelMultiplication(int n) {
    Matrix *A = new Matrix(n);
    Matrix *B = new Matrix(n);
    Matrix *C = new Matrix(n);

    A->fillMatrix();
    B->fillMatrix();

    auto begin = chrono::high_resolution_clock::now();
    parallelMultiply(A, B, C, n);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    delete A, B, C;

    return duration / 1000000.0;
}

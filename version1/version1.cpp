//
// Created by root on 10/8/16.
//

#include <iostream>
#include <chrono>
#include "../utils/MatrixOps.h"
#include "../utils/MiscOps.h"
#include "version1.h"

using namespace std;

void runVersion1() {
    int iterations[] = {218, 7, 3, 3, 3, 3, 3, 3, 3, 3};
    double *durations, avg;
    int n = 0;

    cout << "=========== Running Version 1 ===========" << endl;

    for (int i = 0; i < 10; ++i) {
        n += 100;
        durations = new double[iterations[i]];

        for (int j = 0; j < iterations[i]; ++j)
            durations[j] = getTimeForMultiplication(n);

        avg = average(durations, iterations[i]);

        cout << "For sequential n = " << n << " , average time = " << avg << " ms" << endl;

        delete[] durations;
    }
}

double getTimeForMultiplication(int n) {
    Matrix1D *A = new Matrix1D(n);
    Matrix1D *B = new Matrix1D(n);
    Matrix1D *C = new Matrix1D(n);

    A->fillMatrix();
    B->fillMatrix();

    auto begin = chrono::high_resolution_clock::now();
    multiply1D(A, B, C, n);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    delete A, B, C;

    return duration / 1000000.0;
}

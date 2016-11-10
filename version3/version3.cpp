//
// Created by root on 10/8/16.
//

#include <iostream>
#include <chrono>
#include "version3.h"
#include "../utils/OptimizedMatrixOps.h"
#include "../utils/MiscOps.h"

using namespace std;

void runVersion3(int op) {//24
    int iterations[] = {24, 32, 2, 4, 3, 3, 3, 3, 3, 3, 92, 108, 3, 3, 3, 3, 3, 3, 3, 3};

    double *durations, avg;
    int n = 0, x = 15;

    cout << "=========== Running Version 3 ===========" << endl;

    for (int i = 0; i < 10; ++i) {
        n += (n == 1000) ? -900 : 100;

        switch (op) {
            case 1:
                durations = new double[iterations[i]];

                for (int j = 0; j < iterations[i]; ++j)
                    durations[j] = getTimeForIKJSeq(n);

                avg = average(durations, iterations[i]);
                cout << "For sequential ikj n = " << n << " , average time = " << avg << " ms" << endl;
                break;
            case 2:
                durations = new double[iterations[i + 10]];

                for (int j = 0; j < iterations[i + 10]; ++j)
                    durations[j] = getTimeForIKJParallel(n);

                avg = average(durations, iterations[i + 10]);
                cout << "For parallel ikj n = " << n << " , average time = " << avg << " ms" << endl;
                break;
            case 3:
                durations = new double[x];

                for (int j = 0; j < x; ++j)
                    durations[j] = getTimeForBLASL1(n);

                avg = average(durations, x);
                cout << "For BLAS L1 n = " << n << " , average time = " << avg << " ms" << endl;
                break;
            default:
            case 4:
                durations = new double[x];

                for (int j = 0; j < x; ++j)
                    durations[j] = getTimeForBLASL3(n);

                avg = average(durations, x);
                cout << "For BLAS L3 n = " << n << " , average time = " << avg << " ms" << endl;
                break;
            case 5:
                durations = new double[iterations[i]];

                for (int j = 0; j < iterations[i]; ++j)
                    durations[j] = getTimeForTransposedMultiplication(n);

                avg = average(durations, iterations[i]);
                cout << "For transposed B n = " << n << " , average time = " << avg << " ms" << endl;
                break;
        }

        delete[] durations;
    }
}

double getTimeForIKJSeq(int n) {
    Matrix1D *A = new Matrix1D(n);
    Matrix1D *B = new Matrix1D(n);
    Matrix1D *C = new Matrix1D(n);

    A->fillMatrix();
    B->fillMatrix();

    auto begin = chrono::high_resolution_clock::now();
    multiply1DMatrixIKJ(A, B, C, n);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    delete A, B, C;

    return duration / 1000000.0;
}

double getTimeForIKJParallel(int n) {
    Matrix1D *A = new Matrix1D(n);
    Matrix1D *B = new Matrix1D(n);
    Matrix1D *C = new Matrix1D(n);

    A->fillMatrix();
    B->fillMatrix();

    auto begin = chrono::high_resolution_clock::now();
    parallelMultiply1DMatrixIKJ(A, B, C, n);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    delete A, B, C;

    return duration / 1000000.0;
}

double getTimeForBLASL1(int n) {
    Matrix1D *A = new Matrix1D(n);
    Matrix1D *B = new Matrix1D(n);
    Matrix1D *C = new Matrix1D(n);

    A->fillMatrix();
    B->fillMatrix();

    B = transpose1D(B, n);

    auto begin = chrono::high_resolution_clock::now();
    blasL1(A, B, C, n);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    delete A, B, C;

    return duration / 1000000.0;
}

double getTimeForBLASL3(int n) {
    Matrix1D *A = new Matrix1D(n);
    Matrix1D *B = new Matrix1D(n);
    Matrix1D *C = new Matrix1D(n);

    A->fillMatrix();
    B->fillMatrix();

    B = transpose1D(B, n);

    auto begin = chrono::high_resolution_clock::now();
    blasL3(A, B, C, n);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    delete A, B, C;

    return duration / 1000000.0;
}

double getTimeForTransposedMultiplication(int n) {
    Matrix1D *A = new Matrix1D(n);
    Matrix1D *B = new Matrix1D(n);
    Matrix1D *C = new Matrix1D(n);

    A->fillMatrix();
    B->fillMatrix();

    auto begin = chrono::high_resolution_clock::now();
    transposedParallelMultiply(A, B, C, n);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    delete A, B, C;

    return duration / 1000000.0;
}
#include <iostream>
#include "version1/version1.h"
#include "version2/version2.h"
#include "version3/version3.h"
#include "utils/MiscOps.h"

void printSampleSizes(int version, int op);

using namespace std;

int main(int argc, char *argv[]) {
    int version = (argc > 1) ? stoi(argv[1]) : 0;
    int op = (argc == 3) ? stoi(argv[2]) : argc == 4 ? stoi(argv[3]) : 0;
    int subv = (argc == 3 || argc == 4) ? stoi(argv[2]) : 0;

    switch (version) {
        case 1:
            runVersion1();
            break;
        case 2:
            runVersion2();
            break;
        case 3:
            runVersion3(op);
            break;
        case 4:
            printSampleSizes(subv, op);
            break;
        default:
            cout << "Invalid program version: " << argv[1] << endl;
    }
    return 0;
}

void printSampleSizes(int version, int op) {
    switch (version) {
        case 1:
            cout << "Calculating sample sizes for naive sequential version" << endl;
            break;
        case 2:
            cout << "Calculating sample sizes for parallel version" << endl;
            break;
        case 3:
            switch (op) {
                case 1:
                    cout << "Calculating sample sizes for i-k-j sequential version" << endl;
                    break;
                case 2:
                    cout << "Calculating sample sizes for i-k-j parallel version" << endl;
                    break;
                case 3:
                    cout << "Calculating sample sizes for BLAS level 1 version" << endl;
                    break;
                case 4:
                    cout << "Calculating sample sizes for BLAS level 3 version" << endl;
                    break;
                case 5:
                    cout << "Calculating sample sizes for transposed B version" << endl;
                    break;
            }
            break;
    }

    for (int i = 0, n = 100; i < 10; ++i, n += 100)
        cout << "For n = " << n << ", sample size = " << sampleSize(n, version, op) << endl;
}
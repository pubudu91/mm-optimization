#include <iostream>
#include "version1/version1.h"
#include "version2/version2.h"
#include "version3/version3.h"

using namespace std;

int main(int argc, char *argv[]) {
    switch (stoi(argv[1])) {
        case 1:
            runVersion1();
            break;
        case 2:
            runVersion2();
            break;
        case 3:
            if (argc > 2)
                runVersion3(stoi(argv[2]));
            else
                runVersion3(0);
            break;
        default:
            cout << "Invalid program version: " << argv[1] << endl;
    }
    return 0;
}
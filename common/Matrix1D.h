//
// Created by pubudu on 10/6/16.
//

#ifndef LAB4_5_MATRIX1D_H
#define LAB4_5_MATRIX1D_H

class Matrix1D {
    private:
        const unsigned int size;

    public:
        double *matrix;

        Matrix1D(const unsigned int size);

        ~Matrix1D();

        void printMatrix();

        void fillMatrix();

        const unsigned int getSize() const {
            return size;
        }
};

#endif //LAB4_5_MATRIX1D_H

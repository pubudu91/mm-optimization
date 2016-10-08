//
// Created by root on 10/8/16.
//

#ifndef LAB4_5_FINAL_MATRIX_H
#define LAB4_5_FINAL_MATRIX_H

class Matrix {
    private:
        const unsigned int size;

    public:
        double **matrix;

        Matrix(const unsigned int size);

        virtual ~Matrix();

        void printMatrix();

        void fillMatrix();

        const unsigned int getSize() const {
            return size;
        }
};

#endif //LAB4_5_FINAL_MATRIX_H

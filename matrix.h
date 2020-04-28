#ifndef CASIO_MATRIX_H
#define CASIO_MATRIX_H

struct Matrix {
    int row;
    int col;
    double val[13][13];
    bool created;
};

#endif //CASIO_MATRIX_H
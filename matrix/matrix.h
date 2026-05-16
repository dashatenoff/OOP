#ifndef UNTITLED2_MATRIX_H
#define UNTITLED2_MATRIX_H

#include "field_info.h"

typedef struct {
    void* data;
    int rows;
    int cols;
    const FieldInfo* type;
} Matrix;

Matrix* MatrixCreate(int rows, int cols, const FieldInfo* type);
void MatrixFree(Matrix* matrix);

void* MatrixGet(const Matrix* matrix, int row, int col);
void MatrixSet(Matrix* matrix, int row, int col, const void* value);

Matrix* MatrixAdd(const Matrix* a, const Matrix* b);
Matrix* MatrixMultiply(const Matrix* a, const Matrix* b);
Matrix* MatrixTranspose(const Matrix* a);
Matrix* AddLinearCombination(const Matrix* a, int row, const void* alphas);

void MatrixPrint(const Matrix* m);

#endif //UNTITLED2_MATRIX_H

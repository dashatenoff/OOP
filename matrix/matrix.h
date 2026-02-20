//
// Created by dasha on 18.02.2026.
//

#ifndef UNTITLED2_MATRIX_H
#define UNTITLED2_MATRIX_H

#include "field_info.h"

typedef struct {
    void* data;
    int rows;
    int cols;
    FieldInfo* type;
} Matrix;

Matrix* MatrixCreate(int rows, int cols, FieldInfo* type);
void MatrixFree(Matrix* matrix);

void* MatrixGet(Matrix* matrix, int row, int col);
void MatrixSet(Matrix* matrix, int row, int col, void* value);

Matrix* MatrixAdd(Matrix* a, Matrix* b);
Matrix* MatrixMultiply(Matrix* a, Matrix* b);
Matrix* MatrixTranspose(Matrix* a);
Matrix* AddLinearCombination(Matrix* a, int row, void* alphas);

void MatrixPrint(Matrix* m);

#endif //UNTITLED2_MATRIX_H

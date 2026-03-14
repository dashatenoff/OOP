#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Matrix* MatrixCreate(int rows, int cols, const FieldInfo* type)
{
    if (rows <= 0 || cols <= 0 || type == NULL) {
        fprintf(stderr, "MatrixCreate: invalid parameters\n");
        return NULL;
    }

    Matrix* matrix = malloc(sizeof(Matrix));
    if (matrix == NULL) {
        fprintf(stderr, "MatrixCreate: memory allocation failed\n");
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->type = type;

    matrix->data = malloc((size_t)rows * cols * type->size);
    if (matrix->data == NULL) {
        fprintf(stderr, "MatrixCreate: memory allocation failed\n");
        free(matrix);
        return NULL;
    }

    return matrix;
}

void MatrixFree(Matrix* matrix)
{
    if (matrix == NULL)
        return;

    free(matrix->data);
    free(matrix);
}

void* MatrixGet(const Matrix* matrix, int row, int col)
{
    if (matrix == NULL) {
        fprintf(stderr, "MatrixGet: matrix is NULL\n");
        return NULL;
    }

    if (row < 0 || col < 0 || row >= matrix->rows || col >= matrix->cols) {
        fprintf(stderr, "MatrixGet: index out of bounds\n");
        return NULL;
    }

    return (char*)matrix->data + ((size_t)row * matrix->cols + col) * matrix->type->size;
}

void MatrixSet(Matrix* matrix, int row, int col, const void* value)
{
    if (matrix == NULL || value == NULL) {
        fprintf(stderr, "MatrixSet: NULL argument\n");
        return;
    }

    void* element = MatrixGet(matrix, row, col);
    if (element == NULL)
        return;

    memcpy(element, value, matrix->type->size);
}

Matrix* MatrixAdd(const Matrix* a, const Matrix* b)
{
    if (a == NULL || b == NULL) {
        fprintf(stderr, "MatrixAdd: NULL matrix\n");
        return NULL;
    }

    if (a->rows != b->rows || a->cols != b->cols || a->type != b->type) {
        fprintf(stderr, "MatrixAdd: incompatible matrices\n");
        return NULL;
    }

    Matrix* result = MatrixCreate(a->rows, a->cols, a->type);
    if (result == NULL)
        return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            void* a_el = MatrixGet(a, i, j);
            void* b_el = MatrixGet(b, i, j);
            void* r_el = MatrixGet(result, i, j);

            if (a_el == NULL || b_el == NULL || r_el == NULL) {
                MatrixFree(result);
                return NULL;
            }

            a->type->add(a_el, b_el, r_el);
        }
    }

    return result;
}

Matrix* MatrixMultiply(const Matrix* a, const Matrix* b)
{
    if (a == NULL || b == NULL) {
        fprintf(stderr, "MatrixMultiply: NULL matrix\n");
        return NULL;
    }

    if (a->cols != b->rows || a->type != b->type) {
        fprintf(stderr, "MatrixMultiply: incompatible sizes\n");
        return NULL;
    }

    Matrix* result = MatrixCreate(a->rows, b->cols, a->type);
    if (result == NULL)
        return NULL;

    void* sum = malloc(a->type->size);
    void* mul = malloc(a->type->size);

    if (sum == NULL || mul == NULL) {
        fprintf(stderr, "MatrixMultiply: memory allocation failed\n");
        free(sum);
        free(mul);
        MatrixFree(result);
        return NULL;
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {

            memset(sum, 0, a->type->size);

            for (int k = 0; k < a->cols; k++) {

                void* a_el = MatrixGet(a, i, k);
                void* b_el = MatrixGet(b, k, j);

                if (a_el == NULL || b_el == NULL) {
                    free(sum);
                    free(mul);
                    MatrixFree(result);
                    return NULL;
                }

                a->type->mul(a_el, b_el, mul);
                a->type->add(sum, mul, sum);
            }

            MatrixSet(result, i, j, sum);
        }
    }

    free(sum);
    free(mul);

    return result;
}

Matrix* MatrixTranspose(const Matrix* a)
{
    if (a == NULL) {
        fprintf(stderr, "MatrixTranspose: matrix is NULL\n");
        return NULL;
    }

    Matrix* result = MatrixCreate(a->cols, a->rows, a->type);
    if (result == NULL)
        return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {

            void* value = MatrixGet(a, i, j);
            if (value == NULL) {
                MatrixFree(result);
                return NULL;
            }

            MatrixSet(result, j, i, value);
        }
    }

    return result;
}

Matrix* AddLinearCombination(const Matrix* a, int row, const void* alphas)
{
    if (a == NULL || alphas == NULL) {
        fprintf(stderr, "AddLinearCombination: NULL argument\n");
        return NULL;
    }

    if (row < 0 || row >= a->rows) {
        fprintf(stderr, "AddLinearCombination: invalid row\n");
        return NULL;
    }

    Matrix* result = MatrixCreate(a->rows, a->cols, a->type);
    if (result == NULL)
        return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {

            void* value = MatrixGet(a, i, j);
            if (value == NULL) {
                MatrixFree(result);
                return NULL;
            }

            MatrixSet(result, i, j, value);
        }
    }

    void* mul = malloc(a->type->size);
    if (mul == NULL) {
        fprintf(stderr, "AddLinearCombination: memory allocation failed\n");
        MatrixFree(result);
        return NULL;
    }

    for (int i = 0; i < a->rows; i++) {

        if (i == row)
            continue;

        const void* beta = (const char*)alphas + i * a->type->size;

        for (int j = 0; j < a->cols; j++) {

            void* a_el = MatrixGet(a, i, j);
            void* r_el = MatrixGet(result, row, j);

            if (a_el == NULL || r_el == NULL) {
                free(mul);
                MatrixFree(result);
                return NULL;
            }

            a->type->mul(beta, a_el, mul);
            a->type->add(r_el, mul, r_el);
        }
    }

    free(mul);
    return result;
}

void MatrixPrint(const Matrix* matrix)
{
    if (matrix == NULL) {
        fprintf(stderr, "MatrixPrint: matrix is NULL\n");
        return;
    }

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {

            void* element = MatrixGet(matrix, i, j);

            if (element == NULL)
                printf("NULL ");
            else {
                matrix->type->print(element);
                printf(" ");
            }
        }

        printf("\n");
    }
}
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Matrix* MatrixCreate(int rows, int cols, FieldInfo* type){
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));

    if (matrix == NULL){
        printf("Memory allocation error\n");
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->type = type;
    matrix->data = malloc(rows*cols*type->size);
    if (matrix->data == NULL)
    {
        free(matrix);
        printf("Memory allocation error\n");
        return NULL;
    }
    return matrix;
}

void MatrixFree(Matrix* matrix){
    if (matrix == NULL){
        return;
    }
    free(matrix->data);
    free(matrix);
}

void* MatrixGet(Matrix* matrix, int row, int col){

    if( matrix == NULL || row < 0 || row>=matrix->rows || col < 0 || col>=matrix->cols){
        return NULL;
    }
    return (char*)matrix->data + (row * matrix->cols + col) * matrix->type->size;
}

void MatrixSet(Matrix* matrix, int row, int col, void* value) {
    if (matrix == NULL || value == NULL)
        return;

    void* element = MatrixGet(matrix, row, col);

    if (element == NULL)
        return;

    memcpy(element, value, matrix->type->size);
}

Matrix* MatrixAdd(Matrix* a, Matrix* b){
    if (a == NULL || b == NULL)
        return NULL;
    if (a->rows != b->rows || a->cols != b->cols || a->type != b->type) {
        return NULL;
    }
    Matrix* result = MatrixCreate(a->rows, a->cols, a->type);

    if (result == NULL)
        return NULL;

    for (int i=0; i<a->rows; i++){
        for (int j=0; j<a->cols; j++){
            void* a_el = MatrixGet(a, i, j);
            void* b_el = MatrixGet(b, i, j);
            void* r_el = MatrixGet(result, i, j);

            a->type->add(a_el, b_el, r_el);
        }
    }
    return result;
}


Matrix* MatrixMultiply(Matrix* a, Matrix* b){
    if (a == NULL || b == NULL)
        return NULL;
    if ( a->cols != b->rows || a->type != b->type) {
        return NULL;
    }
    Matrix* result = MatrixCreate(a->rows, b->cols, a->type);

    if (result == NULL)
        return NULL;

    for (int i=0; i<a->rows; i++){
        for (int j=0; j<b->cols; j++){
            void* sum = malloc(a->type->size);
            if (sum == NULL) {
                MatrixFree(result);
                return NULL;
            }
            memset(sum, 0, a->type->size);
            for (int k=0; k<a->cols; k++){
                void* a_el = MatrixGet(a, i, k);
                void* b_el = MatrixGet(b, k, j);
                void* mul = malloc(a->type->size);
                if (mul == NULL) {
                    free(sum);
                    MatrixFree(result);
                    return NULL;
                }

                a->type->mul(a_el, b_el, mul);
                a->type->add(sum, mul, sum);
                free(mul);
            }
            MatrixSet(result, i, j, sum);
            free(sum);
        }
    }

    return result;
}

Matrix* MatrixTranspose(Matrix* a){
    if (a == NULL){
        return NULL;
    }
    Matrix* result = MatrixCreate(a->cols, a->rows, a->type);
    if (result == NULL)
        return NULL;
    for ( int i=0; i<a->rows; i++){
        for (int j=0; j<a->cols; j++){
            void* r = MatrixGet(a, i, j);
            MatrixSet(result, j, i, r);
        }
    }
    return result;
}

Matrix* AddLinearCombination(Matrix* a, int row, void* alphas){
    if (a == NULL){
        return NULL;
    }
    if (alphas == NULL)
        return NULL;
    Matrix* result = MatrixCreate(a->rows, a->cols, a->type);

    if (result == NULL)
        return NULL;

    for (int i=0; i<a->rows; i++){
        for (int j=0; j<a->cols; j++){
            void* value = MatrixGet(a, i,j);
            MatrixSet(result, i, j, value);
        }
    }

    for ( int i=0; i<a->rows; i++) {
        if (i == row)
            continue;

        void *beta = (char *) alphas + i * a->type->size;

        for (int j = 0; j < a->cols; j++) {
            void *a_el = MatrixGet(a, i, j);
            void *r_el = MatrixGet(result, row, j);

            void *mul = malloc(a->type->size);
            if (mul == NULL) {
                MatrixFree(result);
                return NULL;
            }
            a->type->mul(beta, a_el, mul);
            a->type->add(mul, r_el, r_el);
            free(mul);
        }
    }
    return result;
}

void MatrixPrint(Matrix* m){
    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->cols; j++){
            void*
        }
}
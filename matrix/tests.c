#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "field_info.h"
#include "tests.h"

void TestIntAll(){
    printf("TestIntAll:\n");
    FieldInfo* type = GetIntFieldInfo();
    Matrix* A = MatrixCreate(2, 2, type);

    int v;
    v=1;
    MatrixSet(A, 0, 0, &v);
    v = 2;
    MatrixSet(A, 0, 1, &v);
    v = 3;
    MatrixSet(A, 1, 0, &v);
    v = 4;
    MatrixSet(A, 1, 1, &v);

    printf("Matrix A:\n");
    MatrixPrint(A);

    printf("A + A:\n");
    Matrix* S = MatrixAdd(A, A);
    MatrixPrint(S);

    printf("A * A:\n");
    Matrix* M = MatrixMultiply(A, A);
    MatrixPrint(M);

    printf("Transpose:\n");
    Matrix* T = MatrixTranspose(A);
    MatrixPrint(T);

    printf("LinearCombination (row0 + 2*row1):\n");
    int betas[2] = {0, 2};
    Matrix* L = AddLinearCombination(A, 0, betas);
    MatrixPrint(L);

    MatrixFree(A);
    MatrixFree(S);
    MatrixFree(M);
    MatrixFree(T);
    MatrixFree(L);
}

void TestDoubleRectangular()
{
    printf("TestDoubleRectangular (2*3):\n");
    FieldInfo* type = GetDoubleFieldInfo();

    Matrix* A = MatrixCreate(2, 3, type);

    double v;
    v = 1.0;
    MatrixSet(A, 0, 0, &v);
    v = 2.0;
    MatrixSet(A, 0, 1, &v);
    v = 3.0;
    MatrixSet(A, 0, 2, &v);
    v = 4.0;
    MatrixSet(A, 1, 0, &v);
    v = 5.0;
    MatrixSet(A, 1, 1, &v);
    v = 6.0;
    MatrixSet(A, 1, 2, &v);

    printf("Matrix A (2*3):\n");
    MatrixPrint(A);

    printf("Transpose (3*2):\n");
    Matrix* T = MatrixTranspose(A);
    MatrixPrint(T);

    printf("A * T (2x2):\n");
    Matrix* M = MatrixMultiply(A, T);
    MatrixPrint(M);

    printf("LinearCombination (row0 + 2*row1):\n");
    double betas[2] = {0.0, 2.0};
    Matrix* L = AddLinearCombination(A, 0, betas);
    MatrixPrint(L);

    MatrixFree(A);
    MatrixFree(T);
    MatrixFree(M);
    MatrixFree(L);
}

void TestErrors()
{
    printf("estErrors:\n");

    FieldInfo* type = GetIntFieldInfo();

    Matrix* A = MatrixCreate(2, 2, type);
    Matrix* B = MatrixCreate(3, 3, type);


    Matrix* S = MatrixAdd(A, B);
    if (S == NULL)
        printf("Add size mismatch: OK\n");

    // Multiply несовместимых
    Matrix* M = MatrixMultiply(A, B);
    if (M == NULL)
        printf("Multiply size mismatch: OK\n");

    // NULL
    Matrix* N = MatrixAdd
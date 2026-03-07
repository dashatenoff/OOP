#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"
#include "field_info.h"
#include "tests.h"

static double GetTime(clock_t start, clock_t end)
{
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/* =====================================
   TestIntAll
   ===================================== */
void TestIntAll()
{
    printf("\n========== TestIntAll ==========\n");

    FieldInfo* type = GetIntFieldInfo();
    Matrix* A = MatrixCreate(2, 2, type);
    if (!A) {
        printf("Memory error\n");
        return;
    }

    int v;

    v = 1; MatrixSet(A, 0, 0, &v);
    v = 2; MatrixSet(A, 0, 1, &v);
    v = 3; MatrixSet(A, 1, 0, &v);
    v = 4; MatrixSet(A, 1, 1, &v);

    printf("Matrix A:\n");
    MatrixPrint(A);

    /* ---------- ADD ---------- */
    printf("\nTest: A + A\nExpected:\n2 4\n6 8\n");

    clock_t start = clock();
    Matrix* S = MatrixAdd(A, A);
    clock_t end = clock();

    if (!S) {
        printf("Add returned NULL\n");
    } else {
        printf("Result:\n");
        MatrixPrint(S);
        printf("Time: %.6f sec\n", GetTime(start, end));
    }

    /* ---------- MULTIPLY ---------- */
    printf("\nTest: A * A\nExpected:\n7 10\n15 22\n");

    start = clock();
    Matrix* M = MatrixMultiply(A, A);
    end = clock();

    if (!M) {
        printf("Multiply returned NULL\n");
    } else {
        printf("Result:\n");
        MatrixPrint(M);
        printf("Time: %.6f sec\n", GetTime(start, end));
    }

    /* ---------- TRANSPOSE ---------- */
    printf("\nTest: Transpose\nExpected:\n1 3\n2 4\n");

    start = clock();
    Matrix* T = MatrixTranspose(A);
    end = clock();

    if (!T) {
        printf("Transpose returned NULL\n");
    } else {
        printf("Result:\n");
        MatrixPrint(T);
        printf("Time: %.6f sec\n", GetTime(start, end));
    }

    /* ---------- LINEAR COMB ---------- */
    printf("\nTest: row0 + 2*row1\nExpected:\n7 10\n3 4\n");

    int betas[2] = {0, 2};

    start = clock();
    Matrix* L = AddLinearCombination(A, 0, betas);
    end = clock();

    if (!L) {
        printf("LinearCombination returned NULL\n");
    } else {
        printf("Result:\n");
        MatrixPrint(L);
        printf("Time: %.6f sec\n", GetTime(start, end));
    }

    MatrixFree(A);
    MatrixFree(S);
    MatrixFree(M);
    MatrixFree(T);
    MatrixFree(L);
}

/* =====================================
   TestDoubleRectangular
   ===================================== */
void TestDoubleRectangular()
{
    printf("\n========== TestDoubleRectangular ==========\n");

    FieldInfo* type = GetDoubleFieldInfo();
    Matrix* A = MatrixCreate(2, 3, type);
    if (!A) {
        printf("Memory error\n");
        return;
    }

    double v;
    int cnt = 1;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
        {
            v = (double)cnt++;
            MatrixSet(A, i, j, &v);
        }

    printf("Matrix A:\n");
    MatrixPrint(A);

    printf("\nTest: Transpose\n");
    clock_t start = clock();
    Matrix* T = MatrixTranspose(A);
    clock_t end = clock();

    if (T) {
        printf("Result:\n");
        MatrixPrint(T);
        printf("Time: %.6f sec\n", GetTime(start, end));
    }

    printf("\nTest: A * T\n");
    start = clock();
    Matrix* M = MatrixMultiply(A, T);
    end = clock();

    if (M) {
        printf("Result:\n");
        MatrixPrint(M);
        printf("Time: %.6f sec\n", GetTime(start, end));
    }

    MatrixFree(A);
    MatrixFree(T);
    MatrixFree(M);
}

/* =====================================
   TestErrors
   ===================================== */
void TestErrors()
{
    printf("\n========== TestErrors ==========\n");

    FieldInfo* type = GetIntFieldInfo();

    Matrix* A = MatrixCreate(2, 2, type);
    Matrix* B = MatrixCreate(3, 3, type);

    printf("\nTest: Add different sizes (2x2 + 3x3)\nExpected: NULL\n");
    Matrix* S = MatrixAdd(A, B);
    printf("Result: %s\n", S ? "Matrix returned" : "NULL");

    printf("\nTest: Multiply incompatible sizes\nExpected: NULL\n");
    Matrix* M = MatrixMultiply(A, B);
    printf("Result: %s\n", M ? "Matrix returned" : "NULL");

    printf("\nTest: NULL argument\nExpected: NULL\n");
    Matrix* N = MatrixAdd(NULL, A);
    printf("Result: %s\n", N ? "Matrix returned" : "NULL");

    printf("\nTest: wrong row index\nExpected: NULL\n");
    int betas[2] = {1, 1};
    Matrix* L = AddLinearCombination(A, 10, betas);
    printf("Result: %s\n", L ? "Matrix returned" : "NULL");

    MatrixFree(A);
    MatrixFree(B);
}
int MatrixEquals(Matrix* A, Matrix* B, double eps)
{
    if (!A || !B) return 0;
    if (A->rows != B->rows || A->cols != B->cols) return 0;

    double va, vb;

    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->cols; j++)
        {
            MatrixGet(A, i, j);
            MatrixGet(B, i, j);

            if (fabs(va - vb) > eps)
                return 0;
        }

    return 1;
}
void TestLargeMatrix()
{
    printf("\n========== TestLargeMatrix ==========\n");

    FieldInfo* type = GetDoubleFieldInfo();

    int n = 5;   // сначала маленький для проверки
    Matrix* A = MatrixCreate(n, n, type);

    if (!A) {
        printf("Memory error\n");
        return;
    }

    double one = 1.0;

    // Заполняем единицами
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            MatrixSet(A, i, j, &one);

    printf("Matrix A (all ones):\n");
    MatrixPrint(A);

    /* ====== ADD ====== */
    Matrix* S = MatrixAdd(A, A);

    // Эталон
    Matrix* S_true = MatrixCreate(n, n, type);
    double two = 2.0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            MatrixSet(S_true, i, j, &two);

    printf("\nTest: A + A (expected all 2)\n");

    if (MatrixEquals(S, S_true, 1e-9))
        printf("ADD: OK\n");
    else {
        printf("ADD: ERROR\n");
        printf("Program result:\n");
        MatrixPrint(S);
        printf("Correct result:\n");
        MatrixPrint(S_true);
    }

    /* ====== MULTIPLY ====== */
    Matrix* M = MatrixMultiply(A, A);

    Matrix* M_true = MatrixCreate(n, n, type);
    double val = (double)n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            MatrixSet(M_true, i, j, &val);

    printf("\nTest: A * A (expected all %d)\n", n);

    if (MatrixEquals(M, M_true, 1e-9))
        printf("MULTIPLY: OK\n");
    else {
        printf("MULTIPLY: ERROR\n");
        printf("Program result:\n");
        MatrixPrint(M);
        printf("Correct result:\n");
        MatrixPrint(M_true);
    }

    /* ====== TRANSPOSE ====== */
    Matrix* T = MatrixTranspose(A);

    printf("\nTest: Transpose of ones matrix (should be same)\n");

    if (MatrixEquals(T, A, 1e-9))
        printf("TRANSPOSE: OK\n");
    else
        printf("TRANSPOSE: ERROR\n");

    MatrixFree(A);
    MatrixFree(S);
    MatrixFree(S_true);
    MatrixFree(M);
    MatrixFree(M_true);
    MatrixFree(T);
}
/* =====================================
   TestPerformance
   ===================================== */
void TestPerformanceLarge()
{
    printf("\n========== TestPerformanceLarge ==========\n");

    FieldInfo* type = GetDoubleFieldInfo();
    int n = 300;

    Matrix* A = MatrixCreate(n, n, type);
    Matrix* B = MatrixCreate(n, n, type);

    double one = 1.0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            MatrixSet(A, i, j, &one);
            MatrixSet(B, i, j, &one);
        }

    clock_t start = clock();
    Matrix* C = MatrixMultiply(A, B);
    clock_t end = clock();

    printf("Time for %dx%d multiply: %.3f sec\n",
           n, n, GetTime(start, end));


    MatrixFree(A);
    MatrixFree(B);
    MatrixFree(C);
}
/* =====================================
   RunAllTests
   ===================================== */
void RunAllTests()
{
    printf("\n====================================\n");
    printf("RUNNING ALL TESTS\n");
    printf("====================================\n");

    TestIntAll();
    TestDoubleRectangular();
    TestErrors();
    TestLargeMatrix();
    TestPerformanceLarge();

    printf("\n====================================\n");
    printf("ALL TESTS FINISHED\n");
    printf("====================================\n");
}
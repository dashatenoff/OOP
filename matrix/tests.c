#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "matrix.h"
#include "field_info.h"
#include "tests.h"

static double GetTime(clock_t start, clock_t end)
{
    return (double)(end - start) / CLOCKS_PER_SEC;
}

static void PrintResult(const char* name, int ok)
{
    printf("%s: %s\n", name, ok ? "OK" : "FAIL");
}

/* ================= MATRIX EQUAL ================= */

int MatrixEquals(const Matrix* A, const Matrix* B, double eps)
{
    if (!A || !B) return 0;
    if (A->rows != B->rows || A->cols != B->cols) return 0;
    if (A->type != B->type) return 0;

    for(int i = 0; i < A->rows; i++)
    {
        for(int j = 0; j < A->cols; j++)
        {
            if(A->type == GetIntFieldInfo())
            {
                int a = *(int*)MatrixGet(A, i, j);
                int b = *(int*)MatrixGet(B, i, j);

                if(a != b) return 0;
            }
            else
            {
                double a = *(double*)MatrixGet(A, i, j);
                double b = *(double*)MatrixGet(B, i, j);

                if(fabs(a - b) > eps) return 0;
            }
        }
    }

    return 1;
}

/* ================= PRINT MATRIX ================= */

void PrintMatrix(const Matrix* M)
{
    if(!M) return;

    for(int i = 0; i < M->rows; i++)
    {
        for(int j = 0; j < M->cols; j++)
        {
            M->type->print(MatrixGet(M, i, j));
            printf(" ");
        }
        printf("\n");
    }
}

/* ================= CREATE/SET/GET ================= */

void TestCreateSetGet()
{
    printf("\n========== TestCreateSetGet ==========\n");

    FieldInfo* type = GetIntFieldInfo();
    Matrix* A = MatrixCreate(2, 2, type);

    assert(A != NULL);

    int v;

    v = 5; MatrixSet(A, 0, 0, &v);
    v = 7; MatrixSet(A, 0, 1, &v);
    v = 9; MatrixSet(A, 1, 0, &v);
    v = 11; MatrixSet(A, 1, 1, &v);

    assert(*(int*)MatrixGet(A, 0, 0) == 5);
    assert(*(int*)MatrixGet(A, 0, 1) == 7);
    assert(*(int*)MatrixGet(A, 1, 0) == 9);
    assert(*(int*)MatrixGet(A, 1, 1) == 11);

    PrintResult("Create/Set/Get", 1);

    MatrixFree(A);
}

/* ================= INT TESTS ================= */

void TestIntAll()
{
    printf("\n========== TestIntAll ==========\n");

    FieldInfo* type = GetIntFieldInfo();
    Matrix* A = MatrixCreate(2, 2, type);

    assert(A != NULL);

    int v;

    v = 1; MatrixSet(A, 0, 0, &v);
    v = 2; MatrixSet(A, 0, 1, &v);
    v = 3; MatrixSet(A, 1, 0, &v);
    v = 4; MatrixSet(A, 1, 1, &v);

    /* -------- ADD -------- */

    clock_t start = clock();
    Matrix* S = MatrixAdd(A, A);
    clock_t end = clock();

    assert(S != NULL);

    Matrix* S_true = MatrixCreate(2, 2, type);
    assert(S_true != NULL);

    v = 2; MatrixSet(S_true, 0, 0, &v);
    v = 4; MatrixSet(S_true, 0, 1, &v);
    v = 6; MatrixSet(S_true, 1, 0, &v);
    v = 8; MatrixSet(S_true, 1, 1, &v);

    PrintResult("ADD", MatrixEquals(S, S_true, 1e-9));
    assert(MatrixEquals(S, S_true, 1e-9));
    printf("Time: %.6f sec\n", GetTime(start, end));

    /* -------- MULTIPLY -------- */

    start = clock();
    Matrix* M = MatrixMultiply(A, A);
    end = clock();

    assert(M != NULL);

    Matrix* M_true = MatrixCreate(2, 2, type);
    assert(M_true != NULL);

    v = 7;  MatrixSet(M_true, 0, 0, &v);
    v = 10; MatrixSet(M_true, 0, 1, &v);
    v = 15; MatrixSet(M_true, 1, 0, &v);
    v = 22; MatrixSet(M_true, 1, 1, &v);

    PrintResult("MULTIPLY", MatrixEquals(M, M_true, 1e-9));
    assert(MatrixEquals(M, M_true, 1e-9));
    printf("Time: %.6f sec\n", GetTime(start, end));

    /* -------- TRANSPOSE -------- */

    start = clock();
    Matrix* T = MatrixTranspose(A);
    end = clock();

    assert(T != NULL);

    Matrix* T_true = MatrixCreate(2, 2, type);
    assert(T_true != NULL);

    v = 1; MatrixSet(T_true, 0, 0, &v);
    v = 3; MatrixSet(T_true, 0, 1, &v);
    v = 2; MatrixSet(T_true, 1, 0, &v);
    v = 4; MatrixSet(T_true, 1, 1, &v);

    PrintResult("TRANSPOSE", MatrixEquals(T, T_true, 1e-9));
    assert(MatrixEquals(T, T_true, 1e-9));
    printf("Time: %.6f sec\n", GetTime(start, end));

    /* -------- LINEAR COMB -------- */

    int betas[2] = {0, 2};

    start = clock();
    Matrix* L = AddLinearCombination(A, 0, betas);
    end = clock();

    assert(L != NULL);

    Matrix* L_true = MatrixCreate(2, 2, type);
    assert(L_true != NULL);

    v = 7; MatrixSet(L_true, 0, 0, &v);
    v = 10; MatrixSet(L_true, 0, 1, &v);
    v = 3; MatrixSet(L_true, 1, 0, &v);
    v = 4; MatrixSet(L_true, 1, 1, &v);

    PrintResult("LINEAR_COMB", MatrixEquals(L, L_true, 1e-9));
    assert(MatrixEquals(L, L_true, 1e-9));
    printf("Time: %.6f sec\n", GetTime(start, end));

    MatrixFree(A);
    MatrixFree(S);
    MatrixFree(S_true);
    MatrixFree(M);
    MatrixFree(M_true);
    MatrixFree(T);
    MatrixFree(T_true);
    MatrixFree(L);
    MatrixFree(L_true);
}

/* ================= RECTANGULAR ================= */

void TestDoubleRectangular()
{
    printf("\n========== TestDoubleRectangular ==========\n");

    FieldInfo* type = GetDoubleFieldInfo();
    Matrix* A = MatrixCreate(2, 3, type);

    assert(A != NULL);

    double v;
    int cnt = 1;

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            v = (double)cnt++;
            MatrixSet(A, i, j, &v);
        }
    }

    clock_t start = clock();
    Matrix* T = MatrixTranspose(A);
    clock_t end = clock();

    assert(T != NULL);

    Matrix* T_true = MatrixCreate(3, 2, type);
    assert(T_true != NULL);

    v = 1.0; MatrixSet(T_true, 0, 0, &v);
    v = 4.0; MatrixSet(T_true, 0, 1, &v);
    v = 2.0; MatrixSet(T_true, 1, 0, &v);
    v = 5.0; MatrixSet(T_true, 1, 1, &v);
    v = 3.0; MatrixSet(T_true, 2, 0, &v);
    v = 6.0; MatrixSet(T_true, 2, 1, &v);

    PrintResult("DOUBLE_RECTANGULAR_TRANSPOSE", MatrixEquals(T, T_true, 1e-9));
    assert(MatrixEquals(T, T_true, 1e-9));
    printf("Time: %.6f sec\n", GetTime(start, end));

    MatrixFree(A);
    MatrixFree(T);
    MatrixFree(T_true);
}

/* ================= ERROR TESTS ================= */

void TestErrors()
{
    printf("\n========== TestErrors ==========\n");

    FieldInfo* type = GetIntFieldInfo();

    Matrix* A = MatrixCreate(2, 2, type);
    Matrix* B = MatrixCreate(3, 3, type);

    assert(A != NULL);
    assert(B != NULL);

    Matrix* add_result = MatrixAdd(A, B);
    PrintResult("ADD size mismatch", add_result == NULL);
    assert(add_result == NULL);

    Matrix* mult_result = MatrixMultiply(A, B);
    PrintResult("MULTIPLY mismatch", mult_result == NULL);
    assert(mult_result == NULL);

    Matrix* null_result = MatrixAdd(NULL, A);
    PrintResult("NULL argument", null_result == NULL);
    assert(null_result == NULL);

    int betas[2] = {1, 1};
    Matrix* bad_row_result = AddLinearCombination(A, 10, betas);
    PrintResult("BAD ROW", bad_row_result == NULL);
    assert(bad_row_result == NULL);

    MatrixFree(A);
    MatrixFree(B);
}

/* ================= PERFORMANCE ================= */

void TestPerformanceLarge()
{
    printf("\n========== TestPerformanceLarge ==========\n");

    FieldInfo* type = GetDoubleFieldInfo();

    int n = 300;

    Matrix* A = MatrixCreate(n, n, type);
    Matrix* B = MatrixCreate(n, n, type);

    assert(A != NULL);
    assert(B != NULL);

    double one = 1.0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            MatrixSet(A, i, j, &one);
            MatrixSet(B, i, j, &one);
        }
    }

    clock_t start = clock();
    Matrix* C = MatrixMultiply(A, B);
    clock_t end = clock();

    assert(C != NULL);

    printf("Multiply %dx%d time: %.3f sec\n", n, n, GetTime(start, end));

    MatrixFree(A);
    MatrixFree(B);
    MatrixFree(C);
}

void Testbl()
{
    printf("\n========== Testbl ==========\n");

    FieldInfo* type = GetIntFieldInfo();

    Matrix *a = MatrixCreate(2, 2, type);
    Matrix *b = MatrixCreate(2, 2, type);

    assert(a != NULL);
    assert(b != NULL);

    int v;

    v = 1; MatrixSet(a, 0, 0, &v);
    v = 0; MatrixSet(a, 0, 1, &v);
    v = 0; MatrixSet(a, 1, 0, &v);
    v = 1; MatrixSet(a, 1, 1, &v);

    v = 1; MatrixSet(b, 0, 0, &v);
    v = 2; MatrixSet(b, 0, 1, &v);
    v = 3; MatrixSet(b, 1, 0, &v);
    v = 4; MatrixSet(b, 1, 1, &v);

    clock_t start = clock();
    Matrix *c = MatrixAdd(a, b);
    clock_t end = clock();

    assert(c != NULL);

    Matrix *c_true = MatrixCreate(2, 2, type);
    assert(c_true != NULL);

    v = 2; MatrixSet(c_true, 0, 0, &v);
    v = 2; MatrixSet(c_true, 0, 1, &v);
    v = 3; MatrixSet(c_true, 1, 0, &v);
    v = 5; MatrixSet(c_true, 1, 1, &v);

    PrintResult("Testbl ADD", MatrixEquals(c, c_true, 1e-9));
    assert(MatrixEquals(c, c_true, 1e-9));

    printf("Time: %.6f sec\n", GetTime(start, end));

    MatrixFree(a);
    MatrixFree(b);
    MatrixFree(c);
    MatrixFree(c_true);
}

/* ================= RUN ALL ================= */

void RunAllTests()
{
    printf("\n====================================\n");
    printf("RUNNING ALL TESTS\n");
    printf("====================================\n");

    TestCreateSetGet();
    TestIntAll();
    TestDoubleRectangular();
    TestErrors();
    TestPerformanceLarge();
    Testbl();

    printf("\n====================================\n");
    printf("ALL TESTS FINISHED\n");
    printf("====================================\n");
}
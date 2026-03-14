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

static void PrintResult(const char* name, int ok)
{
    printf("%s: %s\n", name, ok ? "OK" : "FAIL");
}

/* ================= MATRIX EQUAL ================= */

int MatrixEquals(const Matrix* A, const Matrix* B, double eps)
{
    if (!A || !B) return 0;
    if (A->rows != B->rows || A->cols != B->cols) return 0;

    for(int i=0;i<A->rows;i++)
        for(int j=0;j<A->cols;j++)
        {
            if(A->type == GetIntFieldInfo())
            {
                int a = *(int*)MatrixGet(A,i,j);
                int b = *(int*)MatrixGet(B,i,j);

                if(a != b) return 0;
            }
            else
            {
                double a = *(double*)MatrixGet(A,i,j);
                double b = *(double*)MatrixGet(B,i,j);

                if(fabs(a-b) > eps) return 0;
            }
        }

    return 1;
}

/* ================= PRINT MATRIX ================= */

void PrintMatrix(const Matrix* M)
{
    if(!M) return;

    for(int i=0;i<M->rows;i++)
    {
        for(int j=0;j<M->cols;j++)
        {
            M->type->print(MatrixGet(M,i,j));
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

    Matrix* A = MatrixCreate(2,2,type);

    int v;

    v=5; MatrixSet(A,0,0,&v);
    v=7; MatrixSet(A,0,1,&v);
    v=9; MatrixSet(A,1,0,&v);
    v=11; MatrixSet(A,1,1,&v);

    printf("Expected matrix:\n");
    printf("5 7\n9 11\n\n");

    printf("Program matrix:\n");
    PrintMatrix(A);

    MatrixFree(A);
}

/* ================= INT TESTS ================= */

void TestIntAll()
{
    printf("\n========== TestIntAll ==========\n");

    FieldInfo* type = GetIntFieldInfo();

    Matrix* A = MatrixCreate(2,2,type);

    int v;

    v=1; MatrixSet(A,0,0,&v);
    v=2; MatrixSet(A,0,1,&v);
    v=3; MatrixSet(A,1,0,&v);
    v=4; MatrixSet(A,1,1,&v);

    printf("\nMatrix A:\n");
    PrintMatrix(A);

    /* -------- ADD -------- */

    printf("\n--- ADD ---\n");
    printf("Expected:\n1+1 2+2\n3+3 4+4\n");

    clock_t start = clock();
    Matrix* S = MatrixAdd(A,A);
    clock_t end = clock();

    printf("\nResult:\n");
    PrintMatrix(S);

    Matrix* S_true = MatrixCreate(2,2,type);

    v=2; MatrixSet(S_true,0,0,&v);
    v=4; MatrixSet(S_true,0,1,&v);
    v=6; MatrixSet(S_true,1,0,&v);
    v=8; MatrixSet(S_true,1,1,&v);

    PrintResult("ADD", MatrixEquals(S,S_true,1e-9));
    printf("Time: %.6f sec\n", GetTime(start,end));

    /* -------- MULTIPLY -------- */

    printf("\n--- MULTIPLY ---\n");
    printf("C[0][0] = 1*1 + 2*3 = 7\n");
    printf("C[0][1] = 1*2 + 2*4 = 10\n");
    printf("C[1][0] = 3*1 + 4*3 = 15\n");
    printf("C[1][1] = 3*2 + 4*4 = 22\n");

    start = clock();
    Matrix* M = MatrixMultiply(A,A);
    end = clock();

    printf("\nResult:\n");
    PrintMatrix(M);

    Matrix* M_true = MatrixCreate(2,2,type);

    v=7; MatrixSet(M_true,0,0,&v);
    v=10; MatrixSet(M_true,0,1,&v);
    v=15; MatrixSet(M_true,1,0,&v);
    v=22; MatrixSet(M_true,1,1,&v);

    PrintResult("MULTIPLY", MatrixEquals(M,M_true,1e-9));
    printf("Time: %.6f sec\n", GetTime(start,end));

    /* -------- TRANSPOSE -------- */

    printf("\n--- TRANSPOSE ---\n");

    start = clock();
    Matrix* T = MatrixTranspose(A);
    end = clock();

    printf("Result:\n");
    PrintMatrix(T);

    Matrix* T_true = MatrixCreate(2,2,type);

    v=1; MatrixSet(T_true,0,0,&v);
    v=3; MatrixSet(T_true,0,1,&v);
    v=2; MatrixSet(T_true,1,0,&v);
    v=4; MatrixSet(T_true,1,1,&v);

    PrintResult("TRANSPOSE", MatrixEquals(T,T_true,1e-9));
    printf("Time: %.6f sec\n", GetTime(start,end));

    /* -------- LINEAR COMB -------- */

    printf("\n--- LINEAR COMBINATION ---\n");
    printf("row0 = row0 + 2*row1\n");

    int betas[2] = {0,2};

    start = clock();
    Matrix* L = AddLinearCombination(A,0,betas);
    end = clock();

    printf("Result:\n");
    PrintMatrix(L);

    Matrix* L_true = MatrixCreate(2,2,type);

    v=7; MatrixSet(L_true,0,0,&v);
    v=10; MatrixSet(L_true,0,1,&v);
    v=3; MatrixSet(L_true,1,0,&v);
    v=4; MatrixSet(L_true,1,1,&v);

    PrintResult("LINEAR_COMB", MatrixEquals(L,L_true,1e-9));
    printf("Time: %.6f sec\n", GetTime(start,end));

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

    Matrix* A = MatrixCreate(2,3,type);

    double v;
    int cnt=1;

    for(int i=0;i<2;i++)
        for(int j=0;j<3;j++)
        {
            v = (double)cnt++;
            MatrixSet(A,i,j,&v);
        }

    printf("\nMatrix A:\n");
    PrintMatrix(A);

    clock_t start = clock();
    Matrix* T = MatrixTranspose(A);
    clock_t end = clock();

    printf("\nTranspose:\n");
    PrintMatrix(T);

    printf("Time: %.6f sec\n", GetTime(start,end));

    MatrixFree(A);
    MatrixFree(T);
}

/* ================= ERROR TESTS ================= */

void TestErrors()
{
    printf("\n========== TestErrors ==========\n");

    FieldInfo* type = GetIntFieldInfo();

    Matrix* A = MatrixCreate(2,2,type);
    Matrix* B = MatrixCreate(3,3,type);

    PrintResult("ADD size mismatch", MatrixAdd(A,B)==NULL);
    PrintResult("MULTIPLY mismatch", MatrixMultiply(A,B)==NULL);
    PrintResult("NULL argument", MatrixAdd(NULL,A)==NULL);

    int betas[2]={1,1};

    PrintResult("BAD ROW",
                AddLinearCombination(A,10,betas)==NULL);

    MatrixFree(A);
    MatrixFree(B);
}

/* ================= PERFORMANCE ================= */

void TestPerformanceLarge()
{
    printf("\n========== TestPerformanceLarge ==========\n");

    FieldInfo* type = GetDoubleFieldInfo();

    int n=300;

    Matrix* A = MatrixCreate(n,n,type);
    Matrix* B = MatrixCreate(n,n,type);

    double one=1.0;

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            MatrixSet(A,i,j,&one);
            MatrixSet(B,i,j,&one);
        }

    clock_t start = clock();
    Matrix* C = MatrixMultiply(A,B);
    clock_t end = clock();

    printf("Multiply %dx%d time: %.3f sec\n",
           n,n,GetTime(start,end));

    MatrixFree(A);
    MatrixFree(B);
    MatrixFree(C);
}

void Testbl(){
    FieldInfo* type = GetIntFieldInfo();
    Matrix *a = MatrixCreate(2, 2,type);
    int v;
    v = 1;
    MatrixSet(a, 0, 0, &v);
    v = 0;
    MatrixSet(a, 0, 1, &v);
    v = 0;
    MatrixSet(a, 1, 0, &v);
    v = 1;
    MatrixSet(a, 1, 1, &v);

    Matrix *b = MatrixCreate(2, 2,type);
    v = 1;
    MatrixSet(b, 0, 0, &v);
    v = 2;
    MatrixSet(b, 0, 1, &v);
    v = 3;
    MatrixSet(b, 1, 0, &v);
    v = 4;
    MatrixSet(b, 1, 1, &v);

    clock_t start = clock();
    Matrix *c = MatrixAdd(a, b);
    clock_t end = clock();
    printf("\nTestbl\n");

    printf("Expected:\n");
    printf("2 2\n3 5\n");

    printf("\nResult:\n");
    MatrixPrint(c);

    printf("Time: %.6f sec\n", GetTime(start,end));

    MatrixFree(a);
    MatrixFree(b);
    MatrixFree(c);
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
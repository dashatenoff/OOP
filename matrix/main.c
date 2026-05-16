#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matrix.h"
#include "field_info.h"
#include "tests.h"

static Matrix* InputMatrix(const FieldInfo* type)
{
    int rows, cols;

    printf("Enter number of rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "Input error\n");
        return NULL;
    }

    Matrix* matrix = MatrixCreate(rows, cols, type);
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    printf("Enter elements:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            if (type->size == sizeof(int)) {
                int value;

                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Input error\n");
                    MatrixFree(matrix);
                    return NULL;
                }

                MatrixSet(matrix, i, j, &value);
            }
            else {
                double value;

                if (scanf("%lf", &value) != 1) {
                    fprintf(stderr, "Input error\n");
                    MatrixFree(matrix);
                    return NULL;
                }

                MatrixSet(matrix, i, j, &value);
            }
        }
    }

    return matrix;
}

static void PrintMenu(void)
{
    printf("\nMenu:\n");
    printf("1 - Add matrices\n");
    printf("2 - Multiply matrices\n");
    printf("3 - Transpose matrix\n");
    printf("4 - Linear combination\n");
    printf("5 - Run tests\n");
    printf("0 - Exit\n");
}

int main(void)
{
    int typeChoice;

    printf("Choose type (1-int, 2-double): ");
    if (scanf("%d", &typeChoice) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }

    const FieldInfo* type;

    if (typeChoice == 1)
        type = GetIntFieldInfo();
    else
        type = GetDoubleFieldInfo();

    int cmd = -1;

    while (cmd != 0)
    {
        PrintMenu();

        printf("Command: ");
        if (scanf("%d", &cmd) != 1) {
            fprintf(stderr, "Input error\n");
            break;
        }

        if (cmd == 1)
        {
            printf("Matrix A:\n");
            Matrix* A = InputMatrix(type);

            printf("Matrix B:\n");
            Matrix* B = InputMatrix(type);

            if (A == NULL || B == NULL) {
                MatrixFree(A);
                MatrixFree(B);
                continue;
            }

            clock_t start = clock();
            Matrix* R = MatrixAdd(A, B);
            clock_t end = clock();

            if (R == NULL)
                printf("Error: incompatible sizes or memory error\n");
            else {
                printf("Result:\n");
                MatrixPrint(R);
                MatrixFree(R);
            }

            MatrixFree(A);
            MatrixFree(B);

            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time: %f seconds\n", time_spent);
        }

        else if (cmd == 2)
        {
            printf("Matrix A:\n");
            Matrix* A = InputMatrix(type);

            printf("Matrix B:\n");
            Matrix* B = InputMatrix(type);

            if (A == NULL || B == NULL) {
                MatrixFree(A);
                MatrixFree(B);
                continue;
            }

            clock_t start = clock();
            Matrix* R = MatrixMultiply(A, B);
            clock_t end = clock();

            if (R == NULL)
                printf("Error: incompatible sizes\n");
            else {
                printf("Result:\n");
                MatrixPrint(R);
                MatrixFree(R);
            }

            MatrixFree(A);
            MatrixFree(B);

            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time: %f seconds\n", time_spent);
        }

        else if (cmd == 3)
        {
            Matrix* A = InputMatrix(type);
            if (A == NULL)
                continue;

            clock_t start = clock();
            Matrix* R = MatrixTranspose(A);
            clock_t end = clock();

            if (R == NULL)
                printf("Error\n");
            else {
                MatrixPrint(R);
                MatrixFree(R);
            }

            MatrixFree(A);

            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time: %f seconds\n", time_spent);
        }

        else if (cmd == 4)
        {
            Matrix* A = InputMatrix(type);
            if (A == NULL)
                continue;

            int row;

            printf("Row index: ");
            if (scanf("%d", &row) != 1) {
                fprintf(stderr, "Input error\n");
                MatrixFree(A);
                continue;
            }

            void* betas = malloc((size_t)A->rows * type->size);
            if (betas == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                MatrixFree(A);
                continue;
            }

            printf("Enter %d coefficients:\n", A->rows);

            for (int i = 0; i < A->rows; i++)
            {
                if (type->size == sizeof(int)) {
                    int value;
                    scanf("%d", &value);
                    memcpy((char*)betas + i * type->size, &value, type->size);
                }
                else {
                    double value;
                    scanf("%lf", &value);
                    memcpy((char*)betas + i * type->size, &value, type->size);
                }
            }

            clock_t start = clock();
            Matrix* R = AddLinearCombination(A, row, betas);
            clock_t end = clock();

            if (R == NULL)
                printf("Error\n");
            else {
                MatrixPrint(R);
                MatrixFree(R);

                double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                printf("Time: %f seconds\n", time_spent);
            }

            free(betas);
            MatrixFree(A);
        }

        else if (cmd == 5)
        {
            RunAllTests();
        }

        else if (cmd == 0)
        {
            printf("Exit\n");
        }

        else
        {
            printf("Unknown command\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matrix.h"
#include "field_info.h"
#include "tests.h"

Matrix* InputMatrix(FieldInfo* type){
    int rows, cols;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    Matrix* m = MatrixCreate(rows, cols, type);
    if (m==NULL){
        printf("Memory error\n");
        return NULL;
    }
    printf("Enter elements:\n");
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++) {
            if (type->size == sizeof(int)) {
                int v;
                scanf("%d", &v);
                MatrixSet(m, i, j , &v);
            } else {
                double v;
                scanf("%lf", &v);
                MatrixSet(m, i, j, &v);
            }
        }
    }
    return m;
}

void PrintMenu(){
    printf("\nMenu:\n");
    printf("1 - Add matrices\n");
    printf("2 - Multiply matrices\n");
    printf("3 - Transpose matrix\n");
    printf("4 - Linear combination\n");
    printf("5 - Run tests\n");
    printf("0 - Exit\n");
}

int main()
{
    int typeChoice;
    printf("Choose type (1-int, 2-double): ");
    scanf("%d", &typeChoice);

    FieldInfo* type;
    if (typeChoice == 1)
        type = GetIntFieldInfo();
    else
        type = GetDoubleFieldInfo();

    int cmd = -1;

    while (cmd != 0)
    {
        PrintMenu();
        printf("Command: ");
        scanf("%d", &cmd);

        if (cmd == 1) // Add
        {


            printf("Matrix A:\n");
            Matrix* A = InputMatrix(type);

            printf("Matrix B:\n");
            Matrix* B = InputMatrix(type);

            clock_t start = clock();
            Matrix* R = MatrixAdd(A, B);
            clock_t end = clock();
            if (R == NULL)
                printf("Error: incompatible sizes or memory error\n");
            else
            {
                printf("Result:\n");
                MatrixPrint(R);
                MatrixFree(R);
            }

            MatrixFree(A);
            MatrixFree(B);

            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time: %f seconds\n", time_spent);
        }

        else if (cmd == 2) // Multiply
        {
            printf("Matrix A:\n");
            Matrix* A = InputMatrix(type);

            printf("Matrix B:\n");
            Matrix* B = InputMatrix(type);

            clock_t start = clock();
            Matrix* R = MatrixMultiply(A, B);
            clock_t end = clock();
            if (R == NULL)
                printf("Error: incompatible sizes\n");
            else
            {
                printf("Result:\n");
                MatrixPrint(R);
                MatrixFree(R);
            }

            MatrixFree(A);
            MatrixFree(B);
            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time: %f seconds\n", time_spent);

        }

        else if (cmd == 3) // Transpose
        {
            Matrix* A = InputMatrix(type);
            clock_t start = clock();
            Matrix* R = MatrixTranspose(A);
            clock_t end = clock();
            if (R == NULL)
                printf("Error\n");
            else
            {
                MatrixPrint(R);
                MatrixFree(R);
            }

            MatrixFree(A);
            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time: %f seconds\n", time_spent);
        }

        else if (cmd == 4) // Linear combination
        {
            Matrix* A = InputMatrix(type);

            int row;
            printf("Row index: ");
            scanf("%d", &row);

            void* betas = malloc(A->rows * type->size);
            if (betas == NULL)
            {
                printf("Memory error\n");
                MatrixFree(A);
                continue;
            }

            printf("Enter %d coefficients:\n", A->rows);

            for (int i = 0; i < A->rows; i++)
            {
                if (type->size == sizeof(int))
                {
                    int v;
                    scanf("%d", &v);
                    memcpy((char*)betas + i*type->size, &v, type->size);
                }
                else
                {
                    double v;
                    scanf("%lf", &v);
                    memcpy((char*)betas + i*type->size, &v, type->size);
                }
            }
            clock_t start = clock();
            Matrix* R = AddLinearCombination(A, row, betas);
            clock_t end = clock();
            if (R == NULL)
                printf("Error\n");
            else
            {
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
#ifndef TESTS_H
#define TESTS_H

#include "matrix.h"

/* comparison */
int MatrixEquals(const Matrix* A, const Matrix* B, double eps);

void PrintMatrix(const Matrix* M);

void TestCreateSetGet();
void TestIntAll();
void TestDoubleRectangular();
void TestErrors();
void TestPerformanceLarge();

void RunAllTests();

#endif

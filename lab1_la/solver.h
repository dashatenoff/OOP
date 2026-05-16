
#ifndef LAB1_LA_SOLVER_H
#define LAB1_LA_SOLVER_H

#include <vector>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

Vector gaussWithoutPivot(Matrix A, Vector b);
Vector gaussWithPivot(Matrix A, Vector b);

void LU(const Matrix& A, Matrix& L, Matrix& U);
Vector forwardSubstitution(const Matrix& L, const Vector& b);
Vector backSubstitution(const Matrix& A, const Vector& b);
Vector solveLU(const Matrix& A, const Vector& b);

Matrix generateMatrix(int n);
Vector generateVector(int n);
#endif //LAB1_LA_SOLVER_H

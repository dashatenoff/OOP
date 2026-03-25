#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#include <stdexcept>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;
const double EPS = 1e-12;

void printVector(const Vector& v){
    for (double x: v){
        std::cout << std::setw(12) << x << " ";
    }
    std::cout << "\n";
}

void printMatrix(const Matrix& A) {
    for (const std::vector<double>& row : A) {
        for (double x : row) {
            std::cout << std::setw(12) << x << " ";
        }
        std::cout << "\n";
    }
}

Vector backSubstitution(const Matrix& A, const Vector& b) {
    int n = A.size();
    Vector x(n);

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;

        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }

        if (std::fabs(A[i][i]) < EPS) {
            throw std::runtime_error("Zero diagonal element in back substitution");
        }

        x[i] = (b[i] - sum) / A[i][i];
    }

    return x;
}

Vector gaussWithoutPivot(Matrix A, Vector b) {
    int n = A.size();

    for (int k = 0; k < n - 1; k++) {
        if (std::fabs(A[k][k]) < EPS) {
            throw std::runtime_error("Zero pivot");
        }

        for (int i = k + 1; i < n; i++) {
            double numb = A[i][k] / A[k][k];

            for (int j = k; j < n; j++) {
                A[i][j] -= numb * A[k][j];
            }

            b[i] -= numb * b[k];
        }
    }

    return backSubstitution(A, b);
}

Vector gaussWithPivot(Matrix A, Vector b) {
    int n = A.size();

    for(int k=0; k<n-1; k++) {
        int pivot = k;
        double maxVal = std::fabs(A[k][k]);

        for (int i = k + 1; i<n; i++ ){
            if (std::fabs(A[i][k]) > maxVal){
                maxVal = std::fabs(A[i][k]);
                pivot = i;
            }
        }
        std::swap(A[k], A[pivot]);
        std::swap(b[k], b[pivot]);

        if (maxVal < EPS) {
            throw std::runtime_error("Zero pivot");
        }

        for( int i=k+1; i<n; i++){
           double numb = A[i][k]/A[k][k];
           for(int j=k; j<n; j++){
               A[i][j]-=(numb*A[k][j]);
           }
           b[i]-=b[k]*numb;
        }
    }
    return backSubstitution(A, b);
}

void LU(const Matrix& A, Matrix& L, Matrix& U){
    int n = A.size();

    L = Matrix(n, Vector(n,0));
    U = A;

    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
    }

    for (int k = 0; k < n - 1; k++) {

        if (std::fabs(U[k][k]) < EPS) {
            throw std::runtime_error("Zero pivot");
        }

        for (int i = k + 1; i < n; i++) {
            double numb = U[i][k] / U[k][k];
            L[i][k] = numb;

            for (int j = k; j < n; j++) {
                U[i][j] = U[i][j] - (numb * U[k][j]);
            }
        }
    }
}

Vector forwardSubstitution(const Matrix& L, const Vector& b) {
    int n = L.size();
    Vector y(n);

    for(int i = 0; i < n; i++){
        double sum = 0.0;
        for (int j = 0; j < i; j++){
            sum += L[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }
    return y;
}

Vector solveLU(const Matrix& A, const Vector& b){
    Matrix L, U;

    LU(A, L, U);
    Vector y = forwardSubstitution(L, b);
    Vector x = backSubstitution(U, y);

    return x;
}

int main() {
    std::cout << "Hello\n";
    return 0;
}

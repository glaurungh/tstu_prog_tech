#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int N1 = 5, N2 = 6, N3 = 7;

const double D1_min = -3.0, D1_max = 3.0;
const double D2_min = -5.0, D2_max = 5.0;
const double D3_min = -2.0, D3_max = 2.0;

const double EPS = 1e-5;

double randDouble(double lo, double hi) {
    return lo + (hi - lo) * (rand() / (double)RAND_MAX);
}

void fillArray(double* arr, int n, double lo, double hi) {
    for (int i = 0; i < n; i++)
        arr[i] = randDouble(lo, hi);
}

void printArray(const char* name, double* arr, int n) {
    cout << name << ": ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << "\t";
    cout << endl;
}


double f(double x, int& k) {
    double result = 1.0;   // n=0: x^0/0! = 1
    double term = 1.0;
    k = 1;
    int n = 1;
    while (true) {
        term *= (x * x) / ((2.0 * n - 1) * (2.0 * n));
        if (fabs(term) < EPS) break;
        result += term;
        k++;
        n++;
    }
    return result;
}

void fillY(double* Y, double* X, int n) {
    for (int i = 0; i < n; i++) {
        int k = 0;
        Y[i] = f(X[i], k);
    }
}

int main() {
    srand((unsigned)time(0));

    double X1[N1], X2[N2], X3[N3];
    double Y1[N1], Y2[N2], Y3[N3];

    fillArray(X1, N1, D1_min, D1_max);
    fillArray(X2, N2, D2_min, D2_max);
    fillArray(X3, N3, D3_min, D3_max);

    fillY(Y1, X1, N1);
    fillY(Y2, X2, N2);
    fillY(Y3, X3, N3);

    cout << "=== Массивы X ===" << endl;
    printArray("X1", X1, N1);
    printArray("X2", X2, N2);
    printArray("X3", X3, N3);

    cout << "\n=== Массивы Y = f(X) ===" << endl;
    printArray("Y1", Y1, N1);
    printArray("Y2", Y2, N2);
    printArray("Y3", Y3, N3);

    return 0;
}

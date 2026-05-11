#include <iostream>
#include <cmath>

using namespace std;

double my_exp(double x) {
    double result = 1.0;
    double term = 1.0;
    int n = 1;
    const double eps = 1e-5;

    while (true) {
        term *= x / n;
        result += term;
        if (fabs(term) < eps)
            return result;
        n++;
    }
}

int main() {
    double a, b;
    cout << "Введите a: ";
    cin >> a;
    cout << "Введите b: ";
    cin >> b;

    double ea = my_exp(a);
    double eb = my_exp(b);
    double r = sqrt(ea + eb);

    cout << "e^a = " << ea << endl;
    cout << "e^b = " << eb << endl;
    cout << "r = sqrt(e^a + e^b) = " << r << endl;

    return 0;
}

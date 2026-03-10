#include <iostream>
#include <cmath>

using namespace std;


double seqPart(double x, int n) {
	int k = 2 * n - 1;
	double sign = (n % 2 == 0) ? -1.0 : 1.0;
	return sign / (k * pow(x, k));
}


int main()
{
	double x;
	cout << "Введите число x: "; 
	cin >> x;

	float eps = 0.001;

	int n = 1;
    
	double term;
	double result = M_PI / 2;
	do {
		term = seqPart(x, n);
		result += term;
		n++;
	} while (fabs(term) > eps);

	cout << "Результат: " << result << endl;
	return 0;
}

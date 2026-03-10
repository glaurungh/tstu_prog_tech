#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int n;
	cout << "Введите целое положительное число: "; 
	cin >> n;
	if (n < 1) {
		cout << "Число должно быть положительным" << std::endl;
		return 1;
	}

	double result = 0;
	int i = n;

	do {
		result = sqrt(i + result);
		i--;

	} while (i > 0);


	cout << "Результат: " << result << endl;
	return 0;
}

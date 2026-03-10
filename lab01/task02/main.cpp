#include <iostream>

using namespace std;

int main()
{
	int number;
	cout << "Введите целое число -> ";
	cin >> number;
	if (number > 0) 
		number++;
	cout << "Число: " << number << endl;
	return 0;
}

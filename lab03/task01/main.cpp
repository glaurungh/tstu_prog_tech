#include <cmath>
#include <iostream>
#include <cfloat>

using namespace std;

void fillArray(double * arr, unsigned length) {
    for (unsigned i=1; i<=length; i++) {
        arr[i-1] = (double)(i-1) / (i + 1) + sin(pow((double)(i-1), 3)/(i+1));
    }
}

void printArray(double * arr, unsigned length) {
    cout << "Оригинальный массив: " << endl;
    for (unsigned i=0; i<length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


void printArrayPositiveMembers(double * arr, unsigned length) {
    cout << "Положительные числа: " << endl;
    for (unsigned i=0; i<length; i++) {
        if (arr[i] > 0)
            cout << arr[i] << " ";
    }
    cout << endl;
}

void findArrayPositiveMinimum(double * arr, unsigned length) {
    cout << "Минимальное положительное число: ";

    double minimum = DBL_MAX;
    for (unsigned i=0; i<length; i++) {
        if (arr[i] > 0 && arr[i] < minimum)
            minimum = arr[i];
    }
    if (minimum == DBL_MAX)
        cout << "отсутствует";
    else
        cout << minimum;
    cout << endl;
}


int main()
{
	unsigned int n;

	cout << "Введите N: ";
	cin >> n;

    double * arr = new double[n];


    fillArray(arr, n);
    printArray(arr, n);
    printArrayPositiveMembers(arr, n);
    findArrayPositiveMinimum(arr, n);

    delete[] arr;


	return 0;
}

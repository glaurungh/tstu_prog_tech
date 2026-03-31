#include <cstdlib>
#include <iostream>

using namespace std;

void fillMatrix(int matrix[], int length) {

    for (int i=0; i<length; i++) {
        matrix[i] = rand() % 9 - 3;
    }
}

void printMatrix(int matrix[], int length) {

    for (int i=0; i<length; i++) {
        cout << matrix[i] << " ";
    }
    cout << endl;
}


double getSequenceMember(int matrix[], int i) {
    int sign = i % 2 == 0 ? 1 : -1;
    int product = 1;
    for (int j = 1; j <= i; j++) {
        product *= j;
    }

    double result;

    result = (double)matrix[i-1] / product;

    return result * sign;
}


int main()
{
	const int N=10;
    int matrix[N];

    srand(time(0));

    fillMatrix(matrix, N);
    printMatrix(matrix, N);

    double result = 0;

    for (int i=1; i<=N; i++) {
        result += getSequenceMember(matrix, i);
    }

    cout << result << endl;

	return 0;
}

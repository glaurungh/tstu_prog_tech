#include <cstdlib>
#include <iostream>

using namespace std;

const int N=10;

void fillMatrixA(int matrix[], int length) {

    for (int i=0; i<length; i++) {
        matrix[i] = rand() % 21 - 5;
    }
}

void printMatrixA(int * matrix, int length) {
    cout << "Матрица А:" << endl;
    for (int i=0; i<length; i++) {
        cout << matrix[i] << " ";
    }
    cout << endl;
}


void printMatrixB(int matrix[][N], int length) {
    cout << "Матрица B:" << endl;
    for (int i=0; i<length; i++) {
        for (int j=0; j<length; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{

    int matrixA[N];
    int matrixB[N][N];

    srand(time(0));

    fillMatrixA(matrixA, N);
    printMatrixA(matrixA, N);

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            matrixB[i][j] = matrixA[i] - 3 * matrixA[j];
        }
    }

    printMatrixB(matrixB, N);

	return 0;
}

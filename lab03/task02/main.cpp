#include <cmath>
#include <cstdlib>
#include <iostream>
#include <cfloat>
#include <iomanip>


using namespace std;

int getRandomNumber(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

void fillMatrix(int** matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = getRandomNumber(-5, 50);
        }
    }
}

void printMatrix(int** matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << setw(2) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


int findMaxAbsValue(int** matrix, unsigned n, unsigned m) {
    int max_abs_value = 0;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            if (abs(matrix[i][j]) > abs(max_abs_value)) {
                max_abs_value = matrix[i][j];
            }
        }
    }
    return max_abs_value;
}

void replaceWithZero(int** matrix, unsigned n, unsigned m, int value) {
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            if (matrix[i][j] == value) {
                matrix[i][j] = 0;
            }
        }
    }
}

void freeMatrix(int** matrix, unsigned n) {
    for (unsigned i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


int main()
{

    std::srand(std::time(0));

	unsigned int n;
	unsigned int m;

	cout << "Введите N: ";
	cin >> n;
	cout << "Введите M: ";
	cin >> m;

    int ** matrix = new int*[n];
    for (unsigned i=0;i<n;i++) {
        matrix[i] = new int[m];
    }


    // Заполнение матрицы случайными числами
    fillMatrix(matrix, n, m);

    cout << "\nИсходная матрица:\n";
    printMatrix(matrix, n, m);

    // Поиск максимального по модулю значения
    int max_abs_value = findMaxAbsValue(matrix, n, m);
    cout << "\nМаксимальное по модулю значение: " << max_abs_value << endl;

    // Замена всех элементов с наибольшим по модулю значением на 0
    replaceWithZero(matrix, n, m, max_abs_value);

    // Вывод результирующей матрицы
    cout << "\nРезультирующая матрица:\n";
    printMatrix(matrix, n, m);

    // Освобождение памяти
    freeMatrix(matrix, n);

	return 0;
}

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int D_LEFT = 0;
const int D_UP = 1;
const int D_RIGHT = 2;
const int D_DOWN = 3;

const int DR[] = { 0, -1,  0, +1 };
const int DC[] = {-1,  0, +1,  0 };


void printMatrix(int** matrix, int n, int width) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(width) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool canGo(int r, int c, int n, bool** visited) {
    return r >= 0 && r < n && c >= 0 && c < n && !visited[r][c];
}

void moveMax(int& r, int& c, int dir, int& num, int n, int** matrix, bool** visited) {
    int dr = DR[dir], dc = DC[dir];
    while (canGo(r + dr, c + dc, n, visited)) {
        r += dr; c += dc;
        matrix[r][c] = num++;
        visited[r][c] = true;
    }
}

bool moveOne(int& r, int& c, int dir, int& num, int n, int** matrix, bool** visited) {
    int dr = DR[dir], dc = DC[dir];
    if (canGo(r + dr, c + dc, n, visited)) {
        r += dr; c += dc;
        matrix[r][c] = num++;
        visited[r][c] = true;
        return true;
    }
    return false;
}

int main() {
    int n;
    cout << "Введите размерность матрицы (n >= 4): ";
    cin >> n;

    if (n < 4) {
        cout << "Ошибка: n должно быть >= 4" << endl;
        return 1;
    }

    int** matrix = new int*[n];
    bool** visited = new bool*[n];
    for (int i = 0; i < n; i++) {
        matrix[i]  = new int[n]();
        visited[i] = new bool[n]();
    }

    int num = 1;
    int r = n - 1, c = n - 1;

    // Старт в правом нижнем углу
    matrix[r][c] = num++;
    visited[r][c] = true;

    // Начало: влево, вверх, вправо, вниз
    moveMax(r, c, D_LEFT, num, n, matrix, visited);   // влево
    moveMax(r, c, D_UP, num, n, matrix, visited);     // вверх
    moveMax(r, c, D_RIGHT, num, n, matrix, visited);  // вправо
    moveMax(r, c, D_DOWN, num, n, matrix, visited);   // вниз

    // Цикл
    while (num <= n * n) {
        int prev = num;

        moveOne(r, c, D_LEFT, num, n, matrix, visited);   // 1 шаг влево
        moveMax(r, c, D_UP, num, n, matrix, visited);     // до упора вверх
        moveMax(r, c, D_LEFT, num, n, matrix, visited);   // до упора влево
        moveMax(r, c, D_DOWN, num, n, matrix, visited);   // до упора вниз
        moveOne(r, c, D_RIGHT, num, n, matrix, visited);  // 1 шаг вправо
        moveMax(r, c, D_UP, num, n, matrix, visited);     // до упора вверх
        moveMax(r, c, D_RIGHT, num, n, matrix, visited);  // до упора вправо
        moveMax(r, c, D_DOWN, num, n, matrix, visited);   // до упора вниз

        if (num == prev) break;
    }

    int width = to_string(n * n).length() + 1;
    printMatrix(matrix, n, width);

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
        delete[] visited[i];
    }
    delete[] matrix;
    delete[] visited;

    return 0;
}

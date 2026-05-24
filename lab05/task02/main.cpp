#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    char expr[255]; // Исходная строка
    cout << "Введите арифметическое выражение (без пробелов, например 10+5*2-8/4): ";
    cin.getline(expr, 255);

    double numbers[100]; // Массив для операндов
    char ops[100];       // Массив для операторов

    int num_count = 0;   // Количество чисел
    int ops_count = 0;   // Количество операций

    char current_number[30]; // Буфер для сборки одного числа
    int c_idx = 0;           // Индекс текущего символа в буфере

    // 1. Парсинг строки
    int len = strlen(expr);
    for (int i = 0; i < len; i++) {
        char c = expr[i];

        if ((c >= '0' && c <= '9') || c == '.') {
            current_number[c_idx++] = c;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            current_number[c_idx] = '\0';
            numbers[num_count++] = atof(current_number);
            ops[ops_count++] = c;
            c_idx = 0;
        }
    }

    // Не забываем добавить последнее число в конце строки
    if (c_idx > 0) {
        current_number[c_idx] = '\0';
        numbers[num_count++] = atof(current_number);
    }

    // 2. Первый проход: умножение и деление
    for (int i = 0; i < ops_count; ) {
        if (ops[i] == '*' || ops[i] == '/') {
            double res = 0;
            if (ops[i] == '*') {
                res = numbers[i] * numbers[i + 1];
            } else {
                res = numbers[i] / numbers[i + 1];
            }

            // Записываем результат на место первого числа
            numbers[i] = res;

            // Сдвигаем оставшиеся числа влево
            for (int j = i + 1; j < num_count - 1; j++) {
                numbers[j] = numbers[j + 1];
            }
            num_count--;

            // Сдвигаем оставшиеся операторы влево
            for (int j = i; j < ops_count - 1; j++) {
                ops[j] = ops[j + 1];
            }
            ops_count--;

            // Индекс i не увеличиваем, так как на место текущей операции встала следующая
        } else {
            i++;
        }
    }

    // 3. Второй проход: сложение и вычитание
    double result = numbers[0];
    for (int i = 0; i < ops_count; i++) {
        if (ops[i] == '+') {
            result += numbers[i + 1];
        } else if (ops[i] == '-') {
            result -= numbers[i + 1];
        }
    }

    cout << "Результат: " << result << endl;

    return 0;
}

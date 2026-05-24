#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

struct STUDENT {
    char name[255];
    int  group;
    int  grades[5];
};

const int N = 10;

double avgGrade(const STUDENT& s) {
    int sum = 0;
    for (int i = 0; i < 5; i++) sum += s.grades[i];
    return sum / 5.0;
}

void inputStudent(STUDENT& s) {
    cout << "  Фамилия и инициалы: ";
    cin.getline(s.name, 255);

    cout << "  Номер группы: ";
    cin >> s.group;

    cout << "  Оценки (5 штук через пробел): ";
    for (int i = 0; i < 5; i++) cin >> s.grades[i];

    cin.ignore();
}

void sortByGroup(STUDENT arr[], int n) {
    STUDENT temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j].group > arr[j + 1].group) {
                temp       = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void sortByName(STUDENT arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        STUDENT min = arr[i];
        int num = i;
        for (int j = i + 1; j < n; j++)
            if (strcmp(arr[j].name, min.name) < 0) {
                min = arr[j];
                num = j;
            }
        arr[num] = arr[i];
        arr[i]   = min;
    }
}

// Вывод на экран
void printHeader() {
    cout << left  << setw(30) << "Фамилия и инициалы           "
         << right << setw(10)  << "Группа    "
         << setw(6) << "О1    " << setw(6) << "О2    "
         << setw(6) << "О3    " << setw(6) << "О4    "
         << setw(6) << "О5    "
         << setw(10) << "Ср.балл" << endl;
    cout << string(78, '-') << endl;
}

void printStudent(const STUDENT& s) {
    cout << left  << setw(30) << s.name
         << right << setw(10)  << s.group;
    for (int i = 0; i < 5; i++) cout << setw(6) << s.grades[i];
    cout << fixed << setprecision(2) << setw(10) << avgGrade(s) << endl;
}

void printAll(STUDENT arr[], int n) {
    printHeader();
    for (int i = 0; i < n; i++) printStudent(arr[i]);
}

// 1. Запись в текстовый файл
void writeToTextFile(STUDENT arr[], int n, const char* filename) {
    ofstream f(filename);
    if (!f.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }
    f << n << "\n"; // Первой строкой пишем количество записей
    for (int i = 0; i < n; i++) {
        f << arr[i].name << "\n";
        f << arr[i].group << "\n";
        for (int j = 0; j < 5; j++)
            f << arr[i].grades[j] << (j < 4 ? " " : "\n");
    }
    f.close();
    cout << "Данные записаны в текстовый файл: " << filename << endl;
}

// 2. Чтение из текстового файла
int readFromTextFile(STUDENT arr[], const char* filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 0;
    }
    int n = 0;
    f >> n;
    f.ignore(); // Пропускаем '\n' после числа
    for (int i = 0; i < n; i++) {
        f.getline(arr[i].name, 255);
        f >> arr[i].group;
        for (int j = 0; j < 5; j++) f >> arr[i].grades[j];
        f.ignore();
    }
    f.close();
    cout << "Данные прочитаны из текстового файла: " << filename << endl;
    return n;
}

// 3. Запись в бинарный файл
void writeToBinFile(STUDENT arr[], int n, const char* filename) {
    // Открываем в бинарном режиме
    ofstream f(filename, ios::binary);
    if (!f.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }
    // Пишем сначала количество записей, затем каждую структуру целиком
    f.write((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++)
        f.write((char*)&arr[i], sizeof(STUDENT));
    f.close();
    cout << "Данные записаны в бинарный файл: " << filename << endl;
}

// 4. Чтение из бинарного файла
int readFromBinFile(STUDENT arr[], const char* filename) {
    ifstream f(filename, ios::binary);
    if (!f.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 0;
    }
    int n = 0;
    f.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++)
        f.read((char*)&arr[i], sizeof(STUDENT));
    f.close();
    cout << "Данные прочитаны из бинарного файла: " << filename << endl;
    return n;
}

// 5. Вывод результатов в текстовый файл
void writeResultsToFile(STUDENT arr[], int n, const char* filename) {
    STUDENT copy[N];
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    ofstream f(filename);
    if (!f.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    // --- Все студенты в алфавитном порядке ---
    sortByName(copy, n);
    f << "=== Все студенты (алфавитный порядок) ===\n";
    f << left  << setw(30) << "Фамилия и инициалы           "
      << right << setw(10)  << "Группа    "
      << setw(6) << "О1    " << setw(6) << "О2    "
      << setw(6) << "О3    " << setw(6) << "О4    "
      << setw(6) << "О5    "
      << setw(10) << "Ср.балл" << "\n";
    f << string(78, '-') << "\n";
    for (int i = 0; i < n; i++) {
        f << left  << setw(30) << copy[i].name
          << right << setw(10)  << copy[i].group;
        for (int j = 0; j < 5; j++) f << setw(6) << copy[i].grades[j];
        f << fixed << setprecision(2) << setw(10) << avgGrade(copy[i]) << "\n";
    }

    // --- Студенты со средним баллом > 4.0 ---
    f << "\n=== Студенты со средним баллом выше 4.0 ===\n";
    f << string(78, '-') << "\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (avgGrade(copy[i]) > 4.0) {
            f << left  << setw(30) << copy[i].name
              << right << setw(8)  << copy[i].group;
            for (int j = 0; j < 5; j++) f << setw(6) << copy[i].grades[j];
            f << fixed << setprecision(2) << setw(10) << avgGrade(copy[i]) << "\n";
            found = true;
        }
    }
    if (!found) f << "Нет студентов со средним баллом выше 4.0.\n";

    f.close();
    cout << "Результаты записаны в файл: " << filename << endl;
}

// Текстовое меню
void printMenu() {
    cout << "\n+--------------------------------------+" << endl;
    cout << "|           МЕНЮ ПРОГРАММЫ             |" << endl;
    cout << "|--------------------------------------|" << endl;
    cout << "| 1. Ввести данные с клавиатуры        |" << endl;
    cout << "| 2. Показать всех студентов на экране |" << endl;
    cout << "| 3. Показать студентов (ср.балл > 4.0)|" << endl;
    cout << "| 4. Записать в текстовый файл         |" << endl;
    cout << "| 5. Прочитать из текстового файла     |" << endl;
    cout << "| 6. Записать в бинарный файл          |" << endl;
    cout << "| 7. Прочитать из бинарного файла      |" << endl;
    cout << "| 8. Сохранить результаты в файл       |" << endl;
    cout << "| 0. Выход                             |" << endl;
    cout << "+--------------------------------------+" << endl;
    cout << "Выберите пункт: ";
}

int main() {
    STUDENT students[N];
    int kol = 0; // Текущее кол-во введенных студентов
    int choice;

    const char* TEXT_FILE   = "students.txt";
    const char* BIN_FILE    = "students.bin";
    const char* RESULT_FILE = "results.txt";

    do {
        printMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1: // Ввод с клавиатуры
            cout << "Сколько студентов ввести (не более " << N << "): ";
            cin >> kol;
            cin.ignore();
            if (kol < 1 || kol > N) {
                cout << "Некорректное количество." << endl;
                kol = 0;
                break;
            }
            for (int i = 0; i < kol; i++) {
                cout << "\nСтудент " << (i + 1) << ":" << endl;
                inputStudent(students[i]);
            }
            sortByGroup(students, kol);
            cout << "Данные введены и отсортированы по номеру группы." << endl;
            break;

        case 2: // Вывод всех на экран
            if (kol == 0) { cout << "Нет данных. Сначала введите студентов." << endl; break; }
            cout << "\n=== Все студенты ===" << endl;
            printAll(students, kol);
            break;

        case 3: // Вывод со средним баллом > 4.0
            if (kol == 0) { cout << "Нет данных." << endl; break; }
            cout << "\n=== Студенты со средним баллом выше 4.0 ===" << endl;
            printHeader();
            {
                bool found = false;
                for (int i = 0; i < kol; i++)
                    if (avgGrade(students[i]) > 4.0) {
                        printStudent(students[i]);
                        found = true;
                    }
                if (!found) cout << "Таких студентов нет." << endl;
            }
            break;

        case 4: // Запись в текстовый файл
            if (kol == 0) { cout << "Нет данных." << endl; break; }
            writeToTextFile(students, kol, TEXT_FILE);
            break;

        case 5: // Чтение из текстового файла
            kol = readFromTextFile(students, TEXT_FILE);
            if (kol > 0) cout << "Загружено студентов: " << kol << endl;
            break;

        case 6: // Запись в бинарный файл
            if (kol == 0) { cout << "Нет данных." << endl; break; }
            writeToBinFile(students, kol, BIN_FILE);
            break;

        case 7: // Чтение из бинарного файла
            kol = readFromBinFile(students, BIN_FILE);
            if (kol > 0) cout << "Загружено студентов: " << kol << endl;
            break;

        case 8: // Сохранение результатов в файл
            if (kol == 0) { cout << "Нет данных." << endl; break; }
            writeResultsToFile(students, kol, RESULT_FILE);
            break;

        case 0:
            cout << "Выход из программы." << endl;
            break;

        default:
            cout << "Неверный пункт меню." << endl;
        }

    } while (choice != 0);

    return 0;
}

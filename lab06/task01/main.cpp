#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct STUDENT {
    char name[255];         // Фамилия и инициалы
    int group;             // Номер группы
    int grades[5];         // Успеваемость (5 оценок)
};

const int N = 10;

double avgGrade(const STUDENT& s) {
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += s.grades[i];
    return sum / 5.0;
}

void inputStudent(STUDENT& s) {
    cout << "  Фамилия и инициалы: ";
    cin.getline(s.name, 50);

    cout << "  Номер группы: ";
    cin >> s.group;

    cout << "  Оценки (5 штук через пробел): ";
    for (int i = 0; i < 5; i++)
        cin >> s.grades[i];

    cin.ignore();
}

void sortByGroup(STUDENT arr[], int n) {
    STUDENT temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j].group > arr[j + 1].group) {
                temp     = arr[j];
                arr[j]   = arr[j + 1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    STUDENT students[N];

    cout << "=== Ввод данных о студентах ===" << endl;
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент " << (i + 1) << ":" << endl;
        inputStudent(students[i]);
    }

    sortByGroup(students, N);

    cout << "\n=== Студенты со средним баллом выше 4.0 ===" << endl;
    cout << "--------------------------------------" << endl;

    bool found = false;
    for (int i = 0; i < N; i++) {
        double avg = avgGrade(students[i]);
        if (avg > 4.0) {
            cout << "Группа: " << students[i].group
                 << " | Студент: " << students[i].name
                 << " | Средний балл: " << avg << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Нет студентов со средним баллом выше 4.0." << endl;
    }

    return 0;
}

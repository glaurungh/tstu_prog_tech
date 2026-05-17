#include <iostream>
#include <cstring>

using namespace std;

const int MAX_CHARS = 1024;


bool isDigit(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

int main() {

    char str[MAX_CHARS];
    char letters[MAX_CHARS];
    char digits[MAX_CHARS];

    cout << "Введите строку: ";

    cin.getline(str, MAX_CHARS);
    int lettersCount = 0, digitsCount = 0;

    for (int i = 0; i < int(strlen(str)); i++) {
        if (isDigit(str[i])) {
            digits[digitsCount++] = str[i];
        } else {
            letters[lettersCount++] = str[i];
        }
    }

    for (int i = 0; i < digitsCount; i++) {
        letters[lettersCount++] = digits[i];
    }

    letters[lettersCount] = '\0';

    cout << letters << endl;

    return 0;
}

#include <iostream>
#include <map>
#include <string>

using namespace std;

// Функция для проверки анаграмм

bool areAnagrams(const string& str1, const string& str2) {
    if (str1.length() != str2.length()) {
        return false; // Если длины строк различаются, они не могут быть анаграммами
    }

    map<char, int> charCount;

    // Подсчитываем символы в первой строке
    for (char ch : str1) {
        charCount[ch]++;
    }

    // Вычитаем символы из второй строки
    for (char ch : str2) {
        charCount[ch]--;
        if (charCount[ch] < 0) {
            return false; // Если количество символов становится отрицательным, строки не анаграммы
        }
    }

    return true; // Если все символы в равном количестве, строки являются анаграммами
}

int main() {
    string str1, str2;

    cout << "Enter the first string: ";
    getline(cin, str1);
    cout << "Enter the second string: ";
    getline(cin, str2);

    if (areAnagrams(str1, str2)) {
        cout << "The strings are anagrams." << endl;
    }
    else {
        cout << "The strings are not anagrams." << endl;
    }

    return 0;
}
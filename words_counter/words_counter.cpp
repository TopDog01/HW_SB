#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("words.txt");
    std::string wordToFind;
    std::string currentWord;
    int count = 0;

    // Проверяем что файл открыт
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    // Запрашиваем слово для поиска
    std::cout << "Enter the word to search: ";
    std::cin >> wordToFind;

    // Читаем слова из файла и считаем количество повторений
    while (inputFile >> currentWord) {
        if (currentWord == wordToFind) {
            count++;
        }
    }

    // Закрываем файл
    inputFile.close();

    // Выводим резулятат
    std::cout << "The word \"" << wordToFind << "\" appears " << count << " time(s) in the file." << std::endl;

    return 0;
}
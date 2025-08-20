#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::string filePath;

    // Запрашиваем у пользователя путь к файлу
    std::cout << "Enter the path to the text file: ";
    std::getline(std::cin, filePath);

    // Открываем файл в бинарном режиме
    std::ifstream inputFile(filePath, std::ios::binary);

    // Проверяем, удалось ли открыть файл
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    // Устанавливаем размер буфера
    const size_t bufferSize = 4096; // Читаем по 4096 байт за раз
    std::vector<char> buffer(bufferSize);

    // Считываем файл и выводим его содержимое
    while (true) {
        inputFile.read(buffer.data(), buffer.size());
        std::streamsize bytesRead = inputFile.gcount();

        if (bytesRead == 0) break; // Выход из цикла, если ничего не прочитано

        // Выводим считанные байты
        std::cout.write(buffer.data(), bytesRead);
    }

    // Закрываем файл
    inputFile.close();

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool isPngFile(const std::string& filePath) {
    // Открыть файл в бинарном режиме
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return false;
    }

    // Считываем первые 4 байта
    std::vector<unsigned char> buffer(4);
    file.read(reinterpret_cast<char*>(buffer.data()), 4);

    // Проверяем, было ли прочитано 4 байта
    if (file.gcount() != 4) {
        std::cerr << "Error: File is too small to be a PNG file." << std::endl;
        return false;
    }

    // Проверка сигнатуры PNG
    if (buffer[0] == 0x89 && buffer[1] == 'P' && buffer[2] == 'N' && buffer[3] == 'G') {
        return true; 
    }

    return false; 
}

int main() {
    std::string filePath;

    // Ввод пути к файлу из стандартного ввода 
    std::cout << "Enter the path to the file: ";
    std::getline(std::cin, filePath);

    // Проверка, является ли файл PNG файлом
    if (isPngFile(filePath)) {
        std::cout << "The file is a valid PNG image." << std::endl;
    }
    else {
        std::cout << "The file is NOT a valid PNG image." << std::endl;
    }

    return 0;
}
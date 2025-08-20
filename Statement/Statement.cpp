#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> // For std::setprecision

struct PaymentRecord {
    std::string name;
    double amount;
    std::string date; // Дата в формате ДД.ММ.ГГГГ
};

int main() {
    std::ifstream inputFile("payments.txt"); // Файл, содержащий данные
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::vector<PaymentRecord> records; // Вектор для хранения записей
    std::string line;
    double totalAmount = 0.0;
    std::string maxRecipient;
    double maxAmount = 0.0;

    // Чтение данных из файла
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        PaymentRecord record;
        if (iss >> record.name >> record.amount >> record.date) {
            // Добавление записи в вектор
            records.push_back(record);
            totalAmount += record.amount; // Общая сумма выплат

            // Проверка, является ли текущий человек максимальным получателем
            if (record.amount > maxAmount) {
                maxAmount = record.amount;
                maxRecipient = record.name;
            }
        }
    }

    
    inputFile.close();

    // Ввывод результатов
    std::cout << std::fixed << std::setprecision(2); // установка формата вывода
    std::cout << "Total amount paid: " << totalAmount << " rubles." << std::endl;
    std::cout << "Person with the highest payment: "
        << maxRecipient << " (" << maxAmount << " rubles)." << std::endl;

    return 0;
}
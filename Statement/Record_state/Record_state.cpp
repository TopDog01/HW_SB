#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

struct PaymentRecord {
    std::string name;
    std::string surname;
    std::string date; // Дата в формате ДД.ММ.ГГГГ
    double amount;    // Сумма выплаты
};

// Функция для проверки корректности даты
bool isValidDate(const std::string& date) {
    if (date.length() != 10 || date[2] != '.' || date[5] != '.')
        return false;

    try {
        int day = std::stoi(date.substr(0, 2));
        int month = std::stoi(date.substr(3, 2));
        int year = std::stoi(date.substr(6, 4));

        // Проверка месяца и дня
        if (month < 1 || month > 12 || day < 1 || day > 31)
            return false;

        // Проверка на количество дней в месяцах
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            return false;
        if (month == 2) {
            // Учёт високосного года
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                if (day > 29) return false;
            }
            else {
                if (day > 28) return false;
            }
        }

        return true;
    }
    catch (...) {
        return false; // В случае ошибки парсинга, считаем дату невалидной
    }
}

// Функция для добавления новой записи
void addRecord(const std::string& filename) {
    PaymentRecord newRecord;

    std::cout << "Enter the recipient's name: ";
    std::cin >> newRecord.name;

    std::cout << "Enter the recipient's surname: ";
    std::cin >> newRecord.surname;

    std::cout << "Enter the issue date (DD.MM.YYYY): ";
    std::cin >> newRecord.date;

    while (!isValidDate(newRecord.date)) {
        std::cout << "Invalid date format. Please enter the date in DD.MM.YYYY format: ";
        std::cin >> newRecord.date;
    }

    std::cout << "Enter the payment amount in rubles: ";
    std::cin >> newRecord.amount;

    // Проверка, что сумма является положительным числом
    while (newRecord.amount < 0) {
        std::cout << "The amount cannot be negative. Please enter a valid amount: ";
        std::cin >> newRecord.amount;
    }

    // Открываем файл для добавления записи
    std::ofstream outfile(filename, std::ios::app); // Открытие файла в режиме добавления

    if (outfile.is_open()) {
        outfile << newRecord.name << " " << newRecord.surname << " "
            << newRecord.date << " " << std::fixed << std::setprecision(2)
            << newRecord.amount << "\n";
        outfile.close();
        std::cout << "Record successfully added.\n";
    }
    else {
        std::cerr << "Failed to open the file for writing.\n";
    }
}

// Функция для отображения всех записей
void listRecords(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }

    std::vector<PaymentRecord> records;
    std::string line;

    // Чтение данных из файла
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        PaymentRecord record;
        if (iss >> record.name >> record.surname >> record.date >> record.amount) {
            records.push_back(record);
        }
    }

    inputFile.close();

    // Вывод записей
    std::cout << "Payment Records:\n";
    for (const auto& record : records) {
        std::cout << record.name << " " << record.surname << " "
            << record.date << " " << std::fixed << std::setprecision(2)
            << record.amount << " rubles." << std::endl;
    }
}

int main() {
    std::string filename = "payments.txt";
    std::string command;

    std::cout << "Enter command (list/add): ";
    std::getline(std::cin, command);

    if (command == "list") {
        listRecords(filename);
    }
    else if (command == "add") {
        addRecord(filename);
    }
    else {
        std::cout << "Unknown command!" << std::endl;
    }

    return 0;
}
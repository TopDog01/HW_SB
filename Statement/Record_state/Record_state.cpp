#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

bool isValidDate(const std::string& date) {
	if (date.length() != 10 || date[2] != '.' || date[5] != '.')
	{
		return false;
	}
	try
	{
		int day = std::stoi(date.substr(0, 2));
		int month = std::stoi(date.substr(3, 2));
		int year = std::stoi(date.substr(6, 4));

		if (month < 1 || month > 12 || day < 1 || day > 31)
		{
			return false;
		}

		//Проверка на количество дней в месяцах

		if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
		if (month == 2)

			//Учет високосного года
		{
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
				if (day > 29) return false;
			}
			else
			{
				if (day > 28) return false;
			}
		}

		return true;
	}
	catch (...) {
		return false; //В случае ошибки парсинга, считаем дату невалидной
	}
}

void addRecord(const std::string& filename) {
	std::string name, surname, date;
	double amount;

	std::cout << "Enter the recipient's name: ";
	std::cin >> name;

	std::cout << "Enter the recipient's surname: ";
	std::cin >> surname;

	std::cout << "Enter the issue date (DD.MM.YYYY): ";
	std::cin >> date;

	while (!isValidDate(date)) {
		std::cout << "Invalid date format. Please enter the date in DD.MM.YYYY format: ";
		std::cin >> date;
	}

	std::cout << "Enter the payment amount in rubles: ";
	std::cin >> amount;

	//Проверка, что сумма является положительным числом

	while (amount < 0) {
		std::cout << "The amount cannot be negative. Please enter a valid amount: ";
		std::cin >> amount;
	}

	//Открываем файл для добавления записи

	std::ofstream outfile;
	outfile.open(filename, std::ios::app); //Открытие файла в режиме добавления

	if (outfile.is_open()) {
		outfile << name << " " << surname << " " << date << " " << std::fixed << std::setprecision(2) << amount << "\n";
		outfile.close();
		std::cout << "Recod successfully added.\n";
	}
	else {
		std::cerr << "Failed to open the file for writing.\n";
	}
}

int main() {
	std::string filename = "payments.txt";
	char choice;

	do {
		addRecord(filename);
		std::cout << "Do you want to add another record? (y/n): ";
		std::cin >> choice;
	} while (choice == 'y' || choice == 'Y');

	return 0;
}
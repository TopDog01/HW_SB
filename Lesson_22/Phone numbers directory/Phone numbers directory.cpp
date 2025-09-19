#include <iostream>
#include <string>
#include <map>
#include <vector>


using namespace std;

// Структура для телефонного справочника
class PhoneBook {
private:
	map<string, string> phoneToName;			// Храним соответствие номер телефона - фамилия
	map<string, vector<string>> nameToPhones;	// Храним соответствие фамилия - список телефонных номеров

public:

	// Метод для добавления записи в телефонный справочник
	void addEntry(const string& phone, const string& name) {
		phoneToName[phone] = name;				

		nameToPhones[name].push_back(phone);
	}

	// Метод для получения фамилии по номеру телефона
	string getNameByPhone(const string& phone) {
		if (phoneToName.find(phone) != phoneToName.end())
		{
			return phoneToName[phone];
		}
		return "Subscriber not found";						
	}

	// Метод для получения номера телефона по фамилии 
	string getPhonesByName(const string& name) {
		if (nameToPhones.find(name) != nameToPhones.end()) {
			string result;
			for (const auto& phone : nameToPhones[name]) {
				result += phone + " ";
			}
			return result;
		}
		return "Name not found";
	}
};

int main() {
	PhoneBook phoneBook;
	string command;

	while (getline(cin, command)) {
		if (command.find(" ") != string::npos) {

			// Запрос на добавление
			size_t spacePos = command.find(" ");
			string phone = command.substr(0, spacePos);
			string name = command.substr(spacePos + 1);
			phoneBook.addEntry(phone, name);
		}
		else
		{
			// Запрос на получении
			string nameOrPhone = command;
			if (nameOrPhone.find("-") != string::npos) {

				// Запрос на получении фамилии по номеру телефона
				cout << phoneBook.getNameByPhone(nameOrPhone) << endl;
			}
			else
			{

				// Запрос на получении номера телефона по фамилии
				cout << phoneBook.getPhonesByName(nameOrPhone) << endl;
			}
		}
	}
	return 0;
}
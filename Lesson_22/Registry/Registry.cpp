#include <iostream>
#include <string>
#include <map>
#include <queue>

int main() {

    std::map<std::string, int> patients; // Хранит количество пациентов с каждой фамилией
    std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> queue; // Очередь для фамилий

    std::string input;

    while (std::cin >> input) {

        if (input == "Next") {

            // Если очередь пуста
            if (queue.empty()) {
                std::cout << "No patients in line" << std::endl;
                continue;
            }

            // Извлекаем фамилию с наименьшим значением (лексикографически)
            std::string next_patient = queue.top();
            queue.pop();

            // Уменьшаем счетчик и удаляем фамилию, если их больше не осталось
            patients[next_patient]--;
            
            if (patients[next_patient] == 0) {
                patients.erase(next_patient);
            }
            std::cout << next_patient << std::endl;
        }
        else {

            // Добавляем фамилию в очередь

            if (patients[input] == 0) {
                queue.push(input); // Добавляем фамилию в очередь только если её нет
            }
            patients[input]++;
        }
    }

    return 0;
}
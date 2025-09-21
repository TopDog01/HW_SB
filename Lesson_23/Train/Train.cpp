#include <iostream>
#include <string>

#define WAGONS 10
#define MAX_PASSENGERS 20

// Макрос для вызова функции
#define CALL(func) { func; }

// Функция для анализа вагонов
void analyzeWagons(int passengers[]) {
    int totalPassengers = 0;

    // Обработка вагонов
    for (int i = 0; i < WAGONS; ++i) {
        totalPassengers += passengers[i];

        // Вывод информации о вагоне
        if (passengers[i] > MAX_PASSENGERS) {
            CALL(std::cout << "Wagon " << i + 1 << " is overfilled whith " << passengers[i] << " passengers." << std::endl);
        }
        else if (passengers[i] < MAX_PASSENGERS) {
            CALL(std::cout << "Wagon " << i + 1 << " has " << (MAX_PASSENGERS - passengers[i]) << " empty seats." << std::endl);
        }
    }

    // Вывод общего количества пассажиров
    CALL(std::cout << "Total number of passengers across all wagons: " << totalPassengers << std::endl);
}

int main() {
    int passengers[WAGONS];

    // Ввод количества пассажиров в каждом вагоне
    std::cout << "Enter the number of passengers in earch of the " << WAGONS << " wagons: " << std::endl;
    for (int i = 0; i < WAGONS; ++i) {
        std::cout << "Wagon " << i + 1 << ": ";
        std::cin >> passengers[i];
    }

    // Анализ вагонов
    analyzeWagons(passengers);

    return 0;
}
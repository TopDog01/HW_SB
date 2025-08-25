#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void catchFish(const std::string& targetFish) {
    std::ifstream riverFile("river.txt");
    std::ofstream basketFile("basket.txt", std::ios::app); // Открыть в режиме добавления

    if (!riverFile.is_open()) {
        std::cerr << "Failed to open river.txt!" << std::endl;
        return;
    }

    if (!basketFile.is_open()) {
        std::cerr << "Failed to open basket.txt!" << std::endl;
        return;
    }

    std::string fish;
    int caughtCount = 0;

    // Чтение рыбы указанной в файле
    while (std::getline(riverFile, fish)) {
        
        fish.erase(remove_if(fish.begin(), fish.end(), isspace), fish.end());

        if (fish == targetFish) {
            basketFile << fish << std::endl; // Записываем пойманную рыбу в корзину
            caughtCount++;
        }
    }

    
    std::cout << "You caught " << caughtCount << " fish(es) of type '" << targetFish << "'!" << std::endl;

    // Закрытие файла
    riverFile.close();
    basketFile.close();
}

int main() {
    std::string target;
    std::cout << "What type of fish are you trying to catch? ";
    std::getline(std::cin, target);

    catchFish(target);

    return 0;
}
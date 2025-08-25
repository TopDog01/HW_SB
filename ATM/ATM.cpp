#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int MAX_BILLS = 1000;
const std::vector<int> denominations = { 5000, 2000, 1000, 500, 200, 100 };

struct ATM {
    int billsCount[6];

    void initialize() {
        std::fill(std::begin(billsCount), std::end(billsCount), 0);
    }

    void loadFromFile() {
        std::ifstream file("atm_state.bin", std::ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(billsCount), sizeof(billsCount));
            file.close();
        }
        else {
            std::cout << "ATM is empty." << std::endl;
        }
    }

    void saveToFile() {
        std::ofstream file("atm_state.bin", std::ios::binary);
        file.write(reinterpret_cast<char*>(billsCount), sizeof(billsCount));
        file.close();
    }

    void displayStatus() {
        int totalCash = 0;
        std::cout << "Current ATM status:" << std::endl;
        for (int i = 0; i < denominations.size(); ++i) {
            std::cout << denominations[i] << "₽: " << billsCount[i] << " bills" << std::endl;
            totalCash += denominations[i] * billsCount[i];
        }
        std::cout << "Total cash in ATM: " << totalCash << "₽" << std::endl;
    }

    void refill() {
        int totalCurrent = 0;
        for (const auto& count : billsCount) {
            totalCurrent += count;
        }

        int billsNeeded = MAX_BILLS - totalCurrent;
        for (int i = 0; i < billsNeeded; ++i) {
            int randomDenomIndex = rand() % denominations.size();
            billsCount[randomDenomIndex]++;
        }
    }

    bool withdraw(int amount) {
        for (int i = 0; i < denominations.size(); ++i) {
            while (amount >= denominations[i] && billsCount[i] > 0) {
                amount -= denominations[i];
                billsCount[i]--;
            }
        }
        return amount == 0;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    ATM atm;
    atm.initialize();
    atm.loadFromFile();
    atm.displayStatus();

    char command;
    while (true) {
        std::cout << "Enter '+' to refill, '-' to withdraw, or 'q' to quit: ";
        std::cin >> command;

        if (command == '+') {
            atm.refill();
            atm.displayStatus();
        }
        else if (command == '-') {
            int amount;
            std::cout << "Enter the amount to withdraw: ";
            std::cin >> amount;

            if (amount % 100 != 0 || amount <= 0) {
                std::cout << "Invalid amount. Amount should be positive and a multiple of 100." << std::endl;
                continue;
            }

            if (atm.withdraw(amount)) {
                atm.displayStatus();
            }
            else {
                std::cout << "Withdrawal impossible. Not enough bills." << std::endl;
            }
        }
        else if (command == 'q') {
            atm.saveToFile();
            std::cout << "ATM state saved. Exiting program." << std::endl;
            break;
        }
        else {
            std::cout << "Unknown command, please try again." << std::endl;
        }
    }

    return 0;
}
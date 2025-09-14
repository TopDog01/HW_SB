#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

// Структура персонажа (героя или врага)
struct Character {
    string name;
    int health;
    int armor;
    int damage;
    char symbol; // символ на карте ('P' для героя, 'E' для врага)
    int x, y;   // координаты на карте
};

const int MAP_SIZE = 20;
Character player;
vector<Character> enemies;

void initGame() {
    srand(time(nullptr)); // инициализация генератора случайных чисел

    // Создаем игрока
    cout << "Enter your character's name: ";
    cin >> player.name;
    player.health = 100;
    player.armor = 20;
    player.damage = 25;
    player.symbol = 'P';
    player.x = rand() % MAP_SIZE;
    player.y = rand() % MAP_SIZE;

    // Генерируем пятерых врагов
    for (int i = 0; i < 5; ++i) {
        Character enemy;
        enemy.name = "Enemy #" + to_string(i + 1);
        enemy.health = rand() % 101 + 50; // от 50 до 150
        enemy.armor = rand() % 51;       // от 0 до 50
        enemy.damage = rand() % 16 + 15; // от 15 до 30
        enemy.symbol = 'E';
        do { // Чтобы избежать совпадения позиций
            enemy.x = rand() % MAP_SIZE;
            enemy.y = rand() % MAP_SIZE;
        } while ((enemy.x == player.x && enemy.y == player.y) || any_of(enemies.begin(), enemies.end(),
            [&](auto& e) { return e.x == enemy.x && e.y == enemy.y; }));
        enemies.push_back(enemy);
    }
}

bool isValidMove(int newX, int newY) {
    return newX >= 0 && newX < MAP_SIZE && newY >= 0 && newY < MAP_SIZE;
}

void movePlayer(const string& command) {
    switch (command.front()) {
    case 'L': --player.x; break;
    case 'R': ++player.x; break;
    case 'U': --player.y; break;
    case 'D': ++player.y; break;
    }
    if (!isValidMove(player.x, player.y)) {
        // Вернуть назад, если вышли за границы карты
        switch (command.front()) {
        case 'L': ++player.x; break;
        case 'R': --player.x; break;
        case 'U': ++player.y; break;
        case 'D': --player.y; break;
        }
    }
}

void attackPlayerIfOnSameCell() {
    for (auto& enemy : enemies) {
        if (player.x == enemy.x && player.y == enemy.y) {
            int actualDamage = max(0, player.damage - enemy.armor); // считаем реальный нанесенный урон
            enemy.health -= actualDamage;
            enemy.armor -= min(actualDamage, enemy.armor); // уменьшить броню также
            cout << "You attacked " << enemy.name << ", causing " << actualDamage << " points of damage." << endl;
            if (enemy.health <= 0) {
                cout << enemy.name << " was defeated!\n";
                enemy.symbol = '.'; // Удаляем противника с карты
            }
        }
    }
}

void moveEnemiesRandomly() {
    vector<string> directions{ "L", "R", "U", "D" };
    for (auto& enemy : enemies) {
        string dir = directions[rand() % 4];
        switch (dir.front()) {
        case 'L': --enemy.x; break;
        case 'R': ++enemy.x; break;
        case 'U': --enemy.y; break;
        case 'D': ++enemy.y; break;
        }
        if (!isValidMove(enemy.x, enemy.y)) {
            // Вернуться обратно, если вышел за карту
            switch (dir.front()) {
            case 'L': ++enemy.x; break;
            case 'R': --enemy.x; break;
            case 'U': ++enemy.y; break;
            case 'D': --enemy.y; break;
            }
        }
    }
}

void displayMap() {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            bool found = false;
            if (player.x == x && player.y == y) {
                cout << player.symbol;
                found = true;
            }
            for (auto& enemy : enemies) {
                if (enemy.x == x && enemy.y == y) {
                    cout << enemy.symbol;
                    found = true;
                    break;
                }
            }
            if (!found) cout << '.';
        }
        cout << '\n';
    }
}

void saveGame(const string& filename) {
    ofstream out(filename, ios::binary | ios::trunc);
    if (!out.is_open()) {
        cerr << "Error opening file for saving.\n";
        return;
    }
    // Записываем игрока
    out.write(reinterpret_cast<const char*>(&player), sizeof(player));
    // Записываем число врагов
    size_t num_enemies = enemies.size();
    out.write(reinterpret_cast<const char*>(&num_enemies), sizeof(num_enemies));
    // Записываем врагов
    for (const auto& enemy : enemies) {
        out.write(reinterpret_cast<const char*>(&enemy), sizeof(enemy));
    }
    out.close();
    cout << "Game saved successfully to " << filename << "\n";
}

void loadGame(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in.is_open()) {
        cerr << "Error opening file for saving..\n";
        return;
    }
    // Читаем игрока
    in.read(reinterpret_cast<char*>(&player), sizeof(player));
    // Число врагов
    size_t num_enemies;
    in.read(reinterpret_cast<char*>(&num_enemies), sizeof(num_enemies));
    enemies.clear(); // очищаем старый список врагов
    // Читаем врагов
    for (size_t i = 0; i < num_enemies; ++i) {
        Character enemy;
        in.read(reinterpret_cast<char*>(&enemy), sizeof(enemy));
        enemies.push_back(enemy);
    }
    in.close();
    cout << "Game saved successfully to " << filename << "\n";
}

void checkWinCondition() {
    bool allDead = true;
    for (const auto& enemy : enemies) {
        if (enemy.health > 0) {
            allDead = false;
            break;
        }
    }
    if (allDead) {
        cout << "Congratulations! All enemies have been defeated!\n";
        exit(EXIT_SUCCESS);
    }
    else if (player.health <= 0) {
        cout << "Your character died... Game over.\n";
        exit(EXIT_FAILURE);
    }
}

int main() {
    initGame();
    string command;
    while (true) {
        displayMap();
        cout << "Enter your action (L/R/U/D to move, save to save, load to load): ";
        cin >> command;
        if (command == "save") {
            saveGame("game_save.bin");
        }
        else if (command == "load") {
            loadGame("game_save.bin");
        }
        else {
            movePlayer(command);
            attackPlayerIfOnSameCell();
            moveEnemiesRandomly();
            checkWinCondition();
        }
    }
    return 0;
}
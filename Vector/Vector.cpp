#include <iostream>
#include <cmath>
#include <iomanip>


struct Vector2D
{
	double x;
    double y;
};

// Функция сложения двух векторов

Vector2D add(const Vector2D& v1, const Vector2D& v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}

// Функция вычитания двух векторов

Vector2D subtract(const Vector2D& v1, const Vector2D& v2) {
	return { v1.x - v2.x, v1.y - v2.y };
}

// Функция умножения вектора на скаляр

Vector2D scale(const Vector2D& v, double scalar) {
	return { v.x * scalar, v.y * scalar };
}

// Функция нахождения длины вектора

double length(const Vector2D& v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

// Функция нормализации вектора

Vector2D normalize(const Vector2D& v) {
	double len = length(v);
	if (len == 0)
	{
		throw std::invalid_argument("Cannot normalize the zero vector.");
	}
	return { v.x / len, v.y / len };
}

int main() {
    std::string operation;
    Vector2D v1, v2;
    double scalar;

    while (true) {
        std::cout << "Enter operation (add, subtract, scale, length, normalize, or exit): ";
        std::cin >> operation;

        if (operation == "exit") {
            break;
        }
        else if (operation == "add" || operation == "subtract") {
            std::cout << "Enter vector1 (x y): ";
            std::cin >> v1.x >> v1.y;
            std::cout << "Enter vector2 (x y): ";
            std::cin >> v2.x >> v2.y;
        }
        else if (operation == "scale") {
            std::cout << "Enter vector (x y): ";
            std::cin >> v1.x >> v1.y;
            std::cout << "Enter scalar: ";
            std::cin >> scalar;
        }
        else if (operation == "length") {
            std::cout << "Enter vector (x y): ";
            std::cin >> v1.x >> v1.y;
        }
        else if (operation == "normalize") {
            std::cout << "Enter vector (x y): ";
            std::cin >> v1.x >> v1.y;
        }
        else {
            std::cout << "Unknown operation!" << std::endl;
            continue;
        }

        if (operation == "add") {
            Vector2D result = add(v1, v2);
            std::cout << "Result: (" << result.x << ", " << result.y << ")" << std::endl;
        }
        else if (operation == "subtract") {
            Vector2D result = subtract(v1, v2);
            std::cout << "Result: (" << result.x << ", " << result.y << ")" << std::endl;
        }
        else if (operation == "scale") {
            Vector2D result = scale(v1, scalar);
            std::cout << "Result: (" << result.x << ", " << result.y << ")" << std::endl;
        }
        else if (operation == "length") {
            double len = length(v1);
            std::cout << "Length: " << len << std::endl;
        }
        else if (operation == "normalize") {
            try {
                Vector2D result = normalize(v1);
                std::cout << "Normalized vector: (" << result.x << ", " << result.y << ")" << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    return 0;
}
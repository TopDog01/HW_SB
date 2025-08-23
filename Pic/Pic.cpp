#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

int main() {
    int width, height;

    // Ask the user for the dimensions of the picture
    std::cout << "Enter the width of the picture: ";
    std::cin >> width;
    std::cout << "Enter the height of the picture: ";
    std::cin >> height;

    // Set the seed for the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create a file pic.txt to write the picture
    std::ofstream outFile("pic.txt");

    if (outFile.is_open()) {
        // Generate random zeros and ones
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                outFile << std::rand() % 2;  // Generate 0 or 1
            }
            outFile << '\n'; // Move to the next line after each row of the picture
        }
        outFile.close();
        std::cout << "Picture created successfully and saved in pic.txt!" << std::endl;
    }
    else {
        std::cout << "Error opening the file!" << std::endl;
    }

    return 0;
}
#include <iostream>

// Определите один из макросов: SPRING, SUMMER, AUTUMN или WINTER
#define SUMMER

#if defined(SPRING)
#define SEASON_NAME "Spring"
#elif defined(SUMMER)
#define SEASON_NAME "Summer"
#elif defined(AUTUMN)
#define SEASON_NAME "Autumn"
#elif defined(WINTER)
#define SEASON_NAME "Winter"
#else
#define SEASON_NAME "Unknown season"
#endif

int main() {


    std::cout << "Current season: " << SEASON_NAME << std::endl;


    return 0;
}

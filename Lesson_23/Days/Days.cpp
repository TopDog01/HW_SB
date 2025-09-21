#include <iostream>


#define DAY_1 "Monday"
#define DAY_2 "Tuesday"
#define DAY_3 "Wednesday"
#define DAY_4 "Thursday"
#define DAY_5 "Friday"
#define DAY_6 "Saturday"
#define DAY_7 "Sunday"




#define GET_DAY(x) ( (x) == 1 ? DAY_1 : \
                     (x) == 2 ? DAY_2 : \
                     (x) == 3 ? DAY_3 : \
                     (x) == 4 ? DAY_4 : \
                     (x) == 5 ? DAY_5 : \
                     (x) == 6 ? DAY_6 : \
                     (x) == 7 ? DAY_7 : "Invalid number" )


int main() {
    int dayNumber;


    std::cout << "Enter the day of the week number (1-7): ";
    std::cin >> dayNumber;


    std::cout << "Day of the week: " << GET_DAY(dayNumber) << std::endl;

    return 0;
}

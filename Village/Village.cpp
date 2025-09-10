#include <iostream>
#include <vector>
#include <string>
#include <numeric> //Для std::accumulate

enum class RoomType
{
	Living,
	Children,
	Bathroom,
	Bedroom,
	Kitchen,
	Other
};

enum class StructureType
{
	House,
	Garage,
	Shed,
	BathHouse
};

//Структура для комнаты
struct Room
{
	RoomType type;
	double ceiling_height;		//Выота потолка
	double area;				//Площадь комнаты

	void fill() {
		int type_int;
		std::cout << " Enter room type (0: Living Room, 1: Children's Room, 2: Bathroom, 3: Bedroom, 4: Kitchen, 5: Other): ";
		std::cin >> type_int;
		type = static_cast<RoomType>(type_int);
		std::cout << " Enter ceiling height (m): ";
		std::cin >> ceiling_height;
		std::cout << " Enter room area (sq.m.): ";
		std::cin >> area;
	}
};

//Структура для этажа
struct Floor
{
	std::vector<Room> rooms;	//Комнаты на этаже
	double area;				//Общая площадь этажа

	void fill() {
		int num_rooms;
		std::cout << " Enter the number of rooms on the floor: ";
		std::cin >> num_rooms;
		rooms.reserve(num_rooms);
		double total_room_area = 0;
		for (int i = 0; i < num_rooms; i++)
		{
			Room room;
			std::cout << " Filling room " << i + 1 << ":" << std::endl;
			room.fill();
			rooms.push_back(room);
			total_room_area += room.area;
		}
		area = total_room_area; //Площадь этажа = сумма площадей комнат
	}
};

//Структура для жилого дома
struct House
{
	std::vector<Floor> floors;	//Этажи дома
	double area;				//Общая площадь дома
	bool has_chimney;			//Печь с трубой

	void fill() {
		int num_floors;
		std::cout << " Enter the number of floors in the house (1-3): ";
		std::cin >> num_floors;
		floors.reserve(num_floors);
		double total_floor_area = 0;

		for (int i = 0; i < num_floors; i++)
		{
			Floor floor;
			std::cout << " Filling floor " << i + 1 << ":" << std::endl;
			floor.fill();
			floors.push_back(floor);
			total_floor_area += floor.area; //Суммируем площадь всех этажей
		}
		area = total_floor_area; //Площадь дома = сумма площадей этажей

		char chimney_choice;
		std::cout << "  Is there a chimney in the house? (y/n): ";
		std::cin >> chimney_choice;
		has_chimney = (chimney_choice == 'y' || chimney_choice == 'Y');
	}
};

//Структура для других построек
struct OtherStructure
{
	StructureType type;
	double area; //Площадь сооружения
	bool has_chimney; //Печь с трубой

	void fill() {
		int type_int;
		std::cout << "    Enter structure type (0: House, 1: Garage, 2: Shed, 3: Bathhouse): ";
		std::cin >> type_int;
		type = static_cast<StructureType>(type_int);

		if (type == StructureType::House) {
			House house;
			house.fill();
			area = house.area;
			has_chimney = house.has_chimney;
		}
		else {
			std::cout << "    Enter structure area (sq.m.): ";
			std::cin >> area;
			if (type == StructureType::BathHouse) {
				char chimney_choice;
				std::cout << "    Is there a chimney in the bathhouse? (y/n): ";
				std::cin >> chimney_choice;
				has_chimney = (chimney_choice == 'y' || chimney_choice == 'Y');
			}
			else {
				has_chimney = false; // Для гаража и сарая печи нет
			}
		}
	}
};

//Структура для участка
struct Plot
{
	int plot_number; 
	std::vector<OtherStructure> structures; // Сооружения на участке
	double total_area; //Общая площадь участка

	void fill() {
		std::cout << "Filling plot #" << plot_number << ":" << std::endl;
		std::cout << "  Enter total area of the plot (sq.m.): ";
		std::cin >> total_area;

		int num_structures;
		std::cout << "  Enter the number of structures on the plot: ";
		std::cin >> num_structures;
		structures.reserve(num_structures);
		for (int i = 0; i < num_structures; ++i) {
			OtherStructure structure;
			std::cout << "  Filling structure " << i + 1 << ":" << std::endl;
			structure.fill();
			structures.push_back(structure);
		}
	}

	double get_structures_area() const {
		double structures_area = 0;
		for (const auto& struct_ : structures) {
			structures_area += struct_.area; //Суммируем площадь всех построек
		}
		return structures_area;
	}
};

//Структура для поселка
struct Village {
	std::vector<Plot> plots; // Участки в поселке
	double total_area; //Общая площадь поселка

	void fill() {
		int num_plots;
		std::cout << "Enter total number of plots in the village: ";
		std::cin >> num_plots;
		plots.reserve(num_plots);
		total_area = 0;

		for (int i = 0; i < num_plots; ++i) {
			Plot plot;
			plot.plot_number = i + 1; // Присваиваем номер участку
			plot.fill();
			plots.push_back(plot);
			total_area += plot.total_area; // Суммируем площадь всех участков
		}
	}

	double calculate_land_coverage_percentage() const {
		if (total_area == 0) return 0.0;
		double total_structures_area = 0;
		for (const auto& plot : plots) {
			total_structures_area += plot.get_structures_area(); // Суммируем площади построек
		}
		return (total_structures_area / total_area) * 100.0; // Процент застроенной площади
	}
};

int main() {
	Village my_village;
	my_village.fill(); // Заполнение информации о поселке

	double land_coverage = my_village.calculate_land_coverage_percentage();
	std::cout << "\n--- Results ---" << std::endl;
	std::cout << "Total area of the village: " << my_village.total_area << " sq.m." << std::endl;
	std::cout << "Percentage of land occupied by structures: " << land_coverage << "%" << std::endl;

	return 0;
}
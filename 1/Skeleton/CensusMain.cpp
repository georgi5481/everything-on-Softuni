#include <iostream>
#include <string>
#include <vector>

#include "City.h"
#include "CityUtils.h"

int main() {
	std::cin.sync_with_stdio(false);
	std::cout.sync_with_stdio(false);

	std::vector<const City*> cities;	//вектора в който ще пълним

	int numCities;
	std::cin >> numCities;	//попълваме инта

	for (int i = 0; i < numCities; i++) {		//колкото пъти сме задали инта
		std::string name;
		size_t population;
		std::cin >> name >> population;		//попъллваме стринга и size_t

		cities.push_back(initCity(name, population));	//вкарваме във вектора след като сме направили обект от класа и ще върнем пойнтера
	}

	size_t totalPopulation;			
	auto citiesByPopulation = groupByPopulation(cities, totalPopulation);		//трябва да върнем мап от size_t и пойнтер към класа

	for (auto populationAndCity : citiesByPopulation) {	//за всички обекти на мапа
		std::cout << populationAndCity.second->getName() << " " << populationAndCity.first << std::endl;		//вторият елемент трябва да е пойнтер и да вика мембъра гетнейм
	}																		//а първият елемент да е size_t
	std::cout << "total: " << totalPopulation << std::endl;	//на края извеждаме сумата на всичките

	for (const City* city : cities) {		//трием всички пойнтери към хийпа
		delete city;
	}

	return 0;
}
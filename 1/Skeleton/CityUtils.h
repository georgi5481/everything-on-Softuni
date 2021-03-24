#ifndef CITY_UTILS
#define CITY_UTILS

#include "City.h"
#include <vector>
#include <map>


City* initCity(std::string& name, size_t& population) {		//елементарна ф-я която връща пойнтер към сити класа
						//вкараваме стринг и size_t

	City* returningPointer = new City(name, population);	//заделяме място в хийпа 

	return returningPointer;	//и просто връщаме пойнтера
}


std::map<size_t,const City*> groupByPopulation(std::vector<const City*>& vectorPointer, size_t& population) {	
																				//2та функция трябва да връща попълнен мап 
																				//катот на 2та позиция ще викаме всеки пойнтер във вектора
	std::map<size_t,const City*> returningMap;	//създаваме мапа
	population = 0;		//зануляваме
	for (const auto& i : vectorPointer) {	//за всеки един елемент във вектора

		returningMap.insert(std::make_pair(i->getPopulation(), i));		//вкарваме всеки конст пойнтер и size_t от класа
		population += i->getPopulation();		//	добавяме вскеки един size_t
	}
	return returningMap;		//връщаме вече попълнен мап
}

#endif // !CITY_UTILS

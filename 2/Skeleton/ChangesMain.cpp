#include "Includes.h"

std::vector<std::pair<City, City> > readCitiesToCompare(int num) {	//вкарали сме колко сравнения искаме да имаме
	std::vector<std::pair<City, City> > result;		//създаване вектор от пейрове от 2 city
	for (int i = 0; i < num; i++) {
		City a, b;
		std::cin >> a >> b;				//колкото пъти сме задали че ще сравняваме, толкова пъти попълваме 2та обекта и ги пейрваме
		result.push_back(std::make_pair(a, b));
	}

	return result;	//връщаме попълнения вектор от пейрове с обектите
}

std::vector<CityDiff> getDifferences(std::vector<std::pair<City, City> > pairs) {	//вкарваме вектора от пейрове с 2та обекта
	std::vector<CityDiff> differences;	//създаваме си вектор с 2рия клас в който да попълваме

	for (auto p : pairs) {			
		differences.push_back(p.first - p.second);		//за всеки един от обектите правим изваждането и попълваме в CityDiff
	}

	return differences;		//връщаме вектора от нашия клас
}

template<typename T>
void printVector(const std::vector<T>& v) {		//вкарваме вектор от CityDiff
	for (auto item : v) {
		std::cout << item;	//извеждаме
	}
}

int main() {
	int numComparisons;
	std::cin >> numComparisons;	//четем колко сравнения искаме да правим
	std::vector<CityDiff> differences = getDifferences(readCitiesToCompare(numComparisons)); //викаме първо readCities а след това getDifferences

	printVector(differences);	//викаме printVector

	return 0;
}
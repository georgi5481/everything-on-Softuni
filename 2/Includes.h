#ifndef INCLUDES_H
#define INCLUDES_H
#include <iostream>
#include <vector>
#include <istream>
#include <ostream>
#include <sstream>
#include "NewCity.h"
 
std::istream& operator>>(std::istream& in, City& city) { 
    return in >> city.name >> city.population >> city.censusYear;
}
 
std::string operator-(City& a, City& b) {
    std::ostringstream result;
    int populInt = a.getPopulation() - b.getPopulation();
    std::string populationResult;
    if (populInt > 0)
        populationResult = "+" + std::to_string(populInt);
    else
        populationResult = std::to_string(populInt);
 
    if (a.getName() == b.getName()) {
        /*- CityName (censusYear1 vs. censusYear2)*/
        result << a.getName() << " (" << a.getCensusYear() << " vs. " << b.getCensusYear() << ") \n" << "population: " << populationResult << "\n";
    }
    else {
        /*- CityName1 (censusYear) vs. CityName2 (censusYear) */
        result << a.getName() << " (" << a.getCensusYear() << ") vs. " << b.getName() << " (" << b.getCensusYear() << ") \n" << "population: " << populationResult << "\n";
    }
    return result.str();
}
 
#endif //!INCLUDES_H
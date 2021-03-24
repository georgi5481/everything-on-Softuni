#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Range.h"

Range readRange(std::string line) {     //вкарваме прочетения стринг от конзолата
    Range r;    //създаваме обект
    std::istringstream in(line);    //наблъскваме стринга в този стрийм

    int number;
    while(in >> number) {   //общо взето преобразуваме стрийма в инт.
        r.add(number);      //вкарваме в обекта инта който сме прочели
    }

    return r;   //връщаме попълнен обекта
}

int main() {
    std::ios::sync_with_stdio(false);

    std::string line;
    std::getline(std::cin, line);

    std::vector<Range> allRanges;

    while(line != "end") {      //четем ред по ред докато не прочетем end
        Range r = readRange(line);      //общо взето създаваме обекта
        allRanges.push_back(r);     //вмъкваме във вектора обекта който създадохме
        std::getline(std::cin, line);   //четем си следващия ред
    }

    int query;
    std::cin >> query;      //четем това което ще търсим

    Range maxOccurrencesRange(allRanges[0]); //създаваме си обект като му подаваме първията обект от вектора(приравняваме ги)
                                             //нарочно приравняваме първият обект за да можем да го използваме при сравнението
    for (size_t i = 1; i < allRanges.size(); i++) {     //от началото до края на вектора
        if (allRanges[i].getCount(query) > maxOccurrencesRange.getCount(query)) {       //проверяваме елемента следващия елемент дали е по-голям от този който сме създали по-горе
            maxOccurrencesRange = allRanges[i]; //ако е по-голям просто го приравняваме с него
        }
    }

    for (T value : maxOccurrencesRange) {   // за всеки обект във вектора
        std::cout << value << " ";      //извеждаме стойността
    }

    return 0;
}

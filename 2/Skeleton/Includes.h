#pragma once
#include<vector>
#include"City.h"
#include<iostream>
#include<sstream>
#include<string>

class CityDiff      //създаваме друг клас който да приема предходния и да правим сметките в него
{
private:
    City left;  //единия сити
    City right;//другия
    unsigned result;    //резултата
    std::string output; 
public:
    CityDiff(City& left, City& right) : left(left), right(right), result(0) {       //когато викнем конструктора вкарваме данните и зануляваме

        if (left.getName() == right.getName())      //ако съвпадат имената
        {
            char sign;  //да се знае знака
            if (left.getPopulation() >= right.getPopulation())  //ако лявото е по-голямо
            {
                result = this->left.getPopulation() - this->right.getPopulation();
                sign = '+';     //вземаме знака и резултата
            }
            else
            {
                result = this->right.getPopulation() - this->left.getPopulation();
                sign = '-'; //взимаме знака и резултата
            }


            std::ostringstream ostr;    //попълващ се стрийм

            if (result != 0)        //ако сезултата е различен от нула се попълва и му даваме знака
                ostr << left.getName() << " (" << std::to_string(left.getCensusYear()) << " vs. " << std::to_string(right.getCensusYear()) << ")"
                << std::endl << "population: " << sign << std::to_string(result) << std::endl;
            else
                ostr << left.getName() << " (" << std::to_string(left.getCensusYear()) << " vs. " << std::to_string(right.getCensusYear()) << ")"
                << std::endl << "population: +" << std::to_string(result) << std::endl;     //внимавай със знака на нулата

            output = ostr.str();    //след като сме попълнили стрийма, го конвертираме към стринг и след това даваме помощния стринг на този
        }
        else
        {
            char sign;      //ако не съвпадат имената се прави същото

            if (left.getPopulation() > right.getPopulation())   //отново проверка за знака
            {
                result = this->left.getPopulation() - this->right.getPopulation();
                sign = '+'; //взимаме си знака и резултата
            }
            else
            {
                result = this->right.getPopulation() - this->left.getPopulation();
                sign = '-'; //взимаме знака и резултата
            }


            std::ostringstream ostr;    
            if (result != 0)
                ostr << left.getName() << " (" << std::to_string(left.getCensusYear()) << ") vs. " << right.getName() << " (" << std::to_string(right.getCensusYear()) << ")"
                << std::endl << "population: " << sign << std::to_string(result) << std::endl;
            else
                ostr << left.getName() << " (" << std::to_string(left.getCensusYear()) << ") vs. " << right.getName() << " (" << std::to_string(right.getCensusYear()) << ")"
                << std::endl << "population: " << std::to_string(result) << std::endl;
            //отново попълваме стрийма само че по малко по-различен начин

            output = ostr.str();        //конвертираме стрийма към стринг и го приравняваме
        }

    }

    std::string getOutput() const       //за вземане на стринга
    {
        return output;
    }

    friend std::ostream& operator<<(std::ostream& out, const CityDiff& obj);    //friend за да може да достъпи на 83-ти ред стрийма в класа
};

std::ostream& operator<<(std::ostream& out, const CityDiff& obj)        //нарочно е отвън за да може да се вика и от мейна
{
    return out << obj.getOutput();      //просто връщаме вече попълнения стрийм
}

std::istream& operator>>(std::istream& in, City& obj)   //ако попълваме сити
{
    unsigned int censusYear;
    std::string name;
    size_t population;

    in >> name >> population >> censusYear;     //даваме едно по едно как да ги запамети
    obj = City(censusYear, name, population);   //създаваме обект към който вече да сочи obj

   return in;      //връщаме си стрийма (все едно е войд функцията)
}

CityDiff operator-(City& left, City& right)     // за да можем да направим сметките направо оувърлоудваме
{
    return CityDiff(left, right);
}


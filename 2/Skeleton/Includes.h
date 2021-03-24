#pragma once
#include<vector>
#include"City.h"
#include<iostream>
#include<sstream>
#include<string>

class CityDiff      //��������� ���� ���� ����� �� ������ ���������� � �� ������ �������� � ����
{
private:
    City left;  //������ ����
    City right;//������
    unsigned result;    //���������
    std::string output; 
public:
    CityDiff(City& left, City& right) : left(left), right(right), result(0) {       //������ ������ ������������ �������� ������� � ����������

        if (left.getName() == right.getName())      //��� �������� �������
        {
            char sign;  //�� �� ���� �����
            if (left.getPopulation() >= right.getPopulation())  //��� ������ � ��-������
            {
                result = this->left.getPopulation() - this->right.getPopulation();
                sign = '+';     //������� ����� � ���������
            }
            else
            {
                result = this->right.getPopulation() - this->left.getPopulation();
                sign = '-'; //������� ����� � ���������
            }


            std::ostringstream ostr;    //�������� �� ������

            if (result != 0)        //��� ��������� � �������� �� ���� �� ������� � �� ������ �����
                ostr << left.getName() << " (" << std::to_string(left.getCensusYear()) << " vs. " << std::to_string(right.getCensusYear()) << ")"
                << std::endl << "population: " << sign << std::to_string(result) << std::endl;
            else
                ostr << left.getName() << " (" << std::to_string(left.getCensusYear()) << " vs. " << std::to_string(right.getCensusYear()) << ")"
                << std::endl << "population: +" << std::to_string(result) << std::endl;     //�������� ��� ����� �� ������

            output = ostr.str();    //���� ���� ��� ��������� �������, �� ������������ ��� ������ � ���� ���� ������ �������� ������ �� ����
        }
        else
        {
            char sign;      //��� �� �������� ������� �� ����� ������

            if (left.getPopulation() > right.getPopulation())   //������ �������� �� �����
            {
                result = this->left.getPopulation() - this->right.getPopulation();
                sign = '+'; //������� �� ����� � ���������
            }
            else
            {
                result = this->right.getPopulation() - this->left.getPopulation();
                sign = '-'; //������� ����� � ���������
            }


            std::ostringstream ostr;    
            if (result != 0)
                ostr << left.getName() << " (" << std::to_string(left.getCensusYear()) << ") vs. " << right.getName() << " (" << std::to_string(right.getCensusYear()) << ")"
                << std::endl << "population: " << sign << std::to_string(result) << std::endl;
            else
                ostr << left.getName() << " (" << std::to_string(left.getCensusYear()) << ") vs. " << right.getName() << " (" << std::to_string(right.getCensusYear()) << ")"
                << std::endl << "population: " << std::to_string(result) << std::endl;
            //������ ��������� ������� ���� �� �� ����� ��-�������� �����

            output = ostr.str();        //������������ ������� ��� ������ � �� ������������
        }

    }

    std::string getOutput() const       //�� ������� �� �������
    {
        return output;
    }

    friend std::ostream& operator<<(std::ostream& out, const CityDiff& obj);    //friend �� �� ���� �� ������� �� 83-�� ��� ������� � �����
};

std::ostream& operator<<(std::ostream& out, const CityDiff& obj)        //������� � ����� �� �� ���� �� �� ���� � �� �����
{
    return out << obj.getOutput();      //������ ������� ���� ���������� ������
}

std::istream& operator>>(std::istream& in, City& obj)   //��� ��������� ����
{
    unsigned int censusYear;
    std::string name;
    size_t population;

    in >> name >> population >> censusYear;     //������ ���� �� ���� ��� �� �� ��������
    obj = City(censusYear, name, population);   //��������� ����� ��� ����� ���� �� ���� obj

   return in;      //������� �� ������� (��� ���� � ���� ���������)
}

CityDiff operator-(City& left, City& right)     // �� �� ����� �� �������� �������� ������� �������������
{
    return CityDiff(left, right);
}


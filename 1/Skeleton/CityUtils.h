#ifndef CITY_UTILS
#define CITY_UTILS

#include "City.h"
#include <vector>
#include <map>


City* initCity(std::string& name, size_t& population) {		//����������� �-� ����� ����� ������� ��� ���� �����
						//��������� ������ � size_t

	City* returningPointer = new City(name, population);	//�������� ����� � ����� 

	return returningPointer;	//� ������ ������� ��������
}


std::map<size_t,const City*> groupByPopulation(std::vector<const City*>& vectorPointer, size_t& population) {	
																				//2�� ������� ������ �� ����� �������� ��� 
																				//����� �� 2�� ������� �� ������ ����� ������� ��� �������
	std::map<size_t,const City*> returningMap;	//��������� ����
	population = 0;		//����������
	for (const auto& i : vectorPointer) {	//�� ����� ���� ������� ��� �������

		returningMap.insert(std::make_pair(i->getPopulation(), i));		//�������� ����� ����� ������� � size_t �� �����
		population += i->getPopulation();		//	�������� ������ ���� size_t
	}
	return returningMap;		//������� ���� �������� ���
}

#endif // !CITY_UTILS

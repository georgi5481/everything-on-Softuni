#include "Includes.h"

std::vector<std::pair<City, City> > readCitiesToCompare(int num) {	//������� ��� ����� ��������� ������ �� �����
	std::vector<std::pair<City, City> > result;		//��������� ������ �� ������� �� 2 city
	for (int i = 0; i < num; i++) {
		City a, b;
		std::cin >> a >> b;				//������� ���� ��� ������ �� �� ����������, ������� ���� ��������� 2�� ������ � �� ��������
		result.push_back(std::make_pair(a, b));
	}

	return result;	//������� ���������� ������ �� ������� � ��������
}

std::vector<CityDiff> getDifferences(std::vector<std::pair<City, City> > pairs) {	//�������� ������� �� ������� � 2�� ������
	std::vector<CityDiff> differences;	//��������� �� ������ � 2��� ���� � ����� �� ���������

	for (auto p : pairs) {			
		differences.push_back(p.first - p.second);		//�� ����� ���� �� �������� ������ ����������� � ��������� � CityDiff
	}

	return differences;		//������� ������� �� ����� ����
}

template<typename T>
void printVector(const std::vector<T>& v) {		//�������� ������ �� CityDiff
	for (auto item : v) {
		std::cout << item;	//���������
	}
}

int main() {
	int numComparisons;
	std::cin >> numComparisons;	//����� ����� ��������� ������ �� ������
	std::vector<CityDiff> differences = getDifferences(readCitiesToCompare(numComparisons)); //������ ����� readCities � ���� ���� getDifferences

	printVector(differences);	//������ printVector

	return 0;
}
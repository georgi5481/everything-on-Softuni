#include "Range.h"


Range::Range() : rangeFirst(0), rangeLength(0), valueCounts(nullptr) {}

void Range::add(int value) {

	if (empty()) {
		resize(value, value);
	}
	else if (value < rangeFirst) {//ако value е по-малко от първия инт на обкласа
		resize(value, rangeFirst + rangeLength);
	}
	else if (value >= (rangeFirst + rangeLength)) //ако е по-голямо или равно
	{
		resize(rangeFirst, value);
	}

	++valueCounts[getIndex(value)];
}
size_t Range::getCount(T value) const {			
	if (value >= rangeFirst + rangeLength || value < rangeFirst) {
		return 0;
	}
	return valueCounts[getIndex(value)];
}

void Range::clear(){
	delete[] valueCounts;
	valueCounts = nullptr;
	rangeFirst = 0;
	rangeLength = 0;
}


void Range::resize(T first, T last) {
	const int new_range = std::abs(last - first) + 1;
	size_t* newValues = new size_t[new_range];
	for (int i = 0; i < new_range; i++) {
		newValues[i] = 0;
	}

	int offset = 0;
	if (first < rangeFirst) {
		offset = rangeFirst - first;
	}

	for (int i = 0; i < rangeLength; i++) {
		newValues[i + offset] = valueCounts[i];
	}

	rangeFirst = first;
	rangeLength = new_range;
	valueCounts = newValues;
}

bool Range::empty() const {
	return valueCounts == nullptr;
}




Range::Range(const Range& other) : rangeFirst(0), rangeLength(0), valueCounts(nullptr){
	if (other.valueCounts) {
		valueCounts = Range::copyValues(other);
		rangeFirst = other.rangeFirst;
		rangeLength = other.rangeLength;
	}
}

Range& Range::operator=(const Range& other) {
	if (this != &other) {
		if (valueCounts) {
			clear();
		}
		if (other.valueCounts) {
			valueCounts = Range::copyValues(other);
			rangeFirst = other.rangeFirst;
			rangeLength = other.rangeLength;
		}
	}
	return *this;
}


Range::~Range() {
	if (valueCounts) {
		clear();
	}
}

size_t Range::getIndex(T value) const{
	return static_cast<size_t>(value - rangeFirst);
}

#ifndef RANGE_H
#define RANGE_H

#include<string>
#include<sstream>
#include<stdexcept>

typedef int T;

class Range {
public:
    class ConstValueIterator {      //��������� ����
        const Range* range;         //����� ������� ����� ��� ����� �� Range(������� ����)
        T currentValue;             //���
        size_t countRemaining;      //unsigned int
    public:
        ConstValueIterator(const Range* range, T currentValue)  //����������� ������� ��������� ������� ��� ������
        : range(range)
        , currentValue(currentValue)
        , countRemaining(0) {   //���� ���� �� ��������� � ����
            if (*this) {    //��� ��������  ��� ���� ����� �� � nullptr
                this->countRemaining = range->getCount(currentValue);   //unsigned int-� �� ���� ��������� ��� unsigned int-a �� ������� ����
            }
        }

        operator bool() const {     //�������������
            return this->currentValue < range->rangeFirst + range->rangeLength && !range->empty();  //��� ���� �� ���� ����� � ��-����� �� ���� ��� ������� ����
                                                                                                    //� ��������� �� ���� ��� ������� ���� � ��-������ �� 0
        }

        const T& operator*() const {    //������ ��������� �� ���� ��� ����� const unsigned int
            if (!*this) 
            {              //��� �������� ��� ���� ����� � nullptr
                throw std::range_error("attempting to dereference end() iterator");  //������� ������
            }

            return currentValue;    //����� const unsigned int
        }

        ConstValueIterator& operator++() {      //�������� ��  ++ 
            this->countRemaining--;     //�������� size_t  � 1
            if (this->countRemaining <= 0) {    //��� size_t � ��-����� ��� ����� �� 0
                while (this->countRemaining <= 0 && *this) {        //������ ����� ������� ����� ��� ����� � size_t � ��-����� ��� ����� �� 0
                    this->currentValue++;           //����������� ���������� �� currentValue � 1
                    this->countRemaining = range->getCount(this->currentValue);     //size_t ����� ����� �� size_t(������ ����� ��� ������� � ������� ����)
                }
            }

            return *this;   //������� �������������� ������� ����� ����� ����� ��� ��������
        }

        //ConstValueIterator operator++(int) {    //������ ���������
        //    ConstValueIterator i = *this;       //��������� ����� ���� �� ��������� ��� �������
        //    this->operator++();                 //�������������� ������
        //    return i;               //������� ���������� � �������� ���� �����
        //}

        bool operator==(const ConstValueIterator& other) const {       //��������� �� ==
            return this->currentValue == other.currentValue &&          //���������� �������� ����� � ��������� ��� ���������
                this->countRemaining == other.countRemaining;
        }

        bool operator!=(const ConstValueIterator& other) const {        //��������� �� !=
            return ! (this->operator==(other));                         //������� ����� ����������� �� ��-������ ��������� � �������� ����� �� �� �� ������ ��������� �����
        }
    };

    Range();

    void add(T value);
    size_t getCount(T value) const;
    void clear();
    void resize(T first, T last);
    bool empty() const;

    Range(const Range& other);
    Range& operator=(const Range& other);
    ~Range();

    ConstValueIterator begin() const {      //�� �� ������ begin()
        return this->empty() ? this->end() : ConstValueIterator(this, rangeFirst);
    }

    ConstValueIterator end() const {        //�� �� ������ end()
        return ConstValueIterator(this, rangeFirst + rangeLength);
    }

    std::string toString() const {      //�������� � ������
        std::ostringstream s;

        for (int i = 0; i < this->rangeLength; i++) {   //�� �������� �� ���� �� range
            s << this->valueCounts[i] << " ";   //�������� � ������� ����� count �� range
        }

        return s.str();     //������� �� ������������� � ������ � �� �������
    }

private:
    T rangeFirst;
    T rangeLength;
    size_t * valueCounts;

    size_t getIndex(T value) const;

    static size_t* copyValues(const Range& other) {     //�������� ���������� ��� ����� Range ����� � const � �� ���� ������� ������� ��� size_t
        return copyValues(other.valueCounts, other.rangeLength);    
    }

    static size_t* copyValues(size_t* values, size_t length) {      //������ ���� ������� �� ��� �� ������ size_t ������� � size_t
        size_t* copies = new size_t[length];        //��������� ����� � ����� ������ ������� lenght
        for (size_t i = 0; i < length; i++) {//�� ���� �� ���� 
            copies[i] = values[i];          //������������ �����������
        }

        return copies;          //������� �������� � ����������� �����
    }
};

#endif // RANGE_H

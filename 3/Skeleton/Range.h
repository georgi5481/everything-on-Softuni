#ifndef RANGE_H
#define RANGE_H

#include<string>
#include<sstream>
#include<stdexcept>

typedef int T;

class Range {
public:
    class ConstValueIterator {      //вътрешния клас
        const Range* range;         //конст пойнтер сочещ към обект от Range(външния клас)
        T currentValue;             //инт
        size_t countRemaining;      //unsigned int
    public:
        ConstValueIterator(const Range* range, T currentValue)  //конструктор вкарващ подадения пойнтер към обекта
        : range(range)
        , currentValue(currentValue)
        , countRemaining(0) {   //също така се изпълнява и кода
            if (*this) {    //ако пойнтера  към този обект не е nullptr
                this->countRemaining = range->getCount(currentValue);   //unsigned int-а ще бъде приравнен към unsigned int-a на външния клас
            }
        }

        operator bool() const {     //оувърлоудваме
            return this->currentValue < range->rangeFirst + range->rangeLength && !range->empty();  //ако инта на този обект е по-малък от инта във външния клас
                                                                                                    //и дължината на инта във външния клас е по-голяма от 0
        }

        const T& operator*() const {    //отново оувърлоуд но този път връща const unsigned int
            if (!*this) 
            {              //ако пойнтера към този обект е nullptr
                throw std::range_error("attempting to dereference end() iterator");  //извежда грешка
            }

            return currentValue;    //връща const unsigned int
        }

        ConstValueIterator& operator++() {      //овърлоуд на  ++ 
            this->countRemaining--;     //намаляме size_t  с 1
            if (this->countRemaining <= 0) {    //ако size_t е по-малко или равно на 0
                while (this->countRemaining <= 0 && *this) {        //докато имаме пойнтер сочещ към обект и size_t е по-малък или равен на 0
                    this->currentValue++;           //увеличаваме стойността на currentValue с 1
                    this->countRemaining = range->getCount(this->currentValue);     //size_t става равно на size_t(метода който сме описали в главния клас)
                }
            }

            return *this;   //връщаме дереференциран дадения обект върху който сме работили
        }

        //ConstValueIterator operator++(int) {    //отново оувърлоуд
        //    ConstValueIterator i = *this;       //създаваме обект като го приравним към дадения
        //    this->operator++();                 //инкрементираме обекта
        //    return i;               //връщаме създадения и попълнен вече обект
        //}

        bool operator==(const ConstValueIterator& other) const {       //оувърлоуд на ==
            return this->currentValue == other.currentValue &&          //сравняваме сегашния обект и подадения във функцията
                this->countRemaining == other.countRemaining;
        }

        bool operator!=(const ConstValueIterator& other) const {        //оувърлоуд на !=
            return ! (this->operator==(other));                         //връщаме първо сравнението от по-горния оувърлоуд и обръщаме знака за да се получи огледален ефект
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

    ConstValueIterator begin() const {      //за да вземем begin()
        return this->empty() ? this->end() : ConstValueIterator(this, rangeFirst);
    }

    ConstValueIterator end() const {        //за да вземем end()
        return ConstValueIterator(this, rangeFirst + rangeLength);
    }

    std::string toString() const {      //обръщаме в стринг
        std::ostringstream s;

        for (int i = 0; i < this->rangeLength; i++) {   //от началото до края на range
            s << this->valueCounts[i] << " ";   //вкарваме в стрийма всеки count за range
        }

        return s.str();     //стрийма го преобразуваме в стринг и го връщаме
    }

private:
    T rangeFirst;
    T rangeLength;
    size_t * valueCounts;

    size_t getIndex(T value) const;

    static size_t* copyValues(const Range& other) {     //вкарваме референция към обект Range който е const и на края връщаме пойнтер към size_t
        return copyValues(other.valueCounts, other.rangeLength);    
    }

    static size_t* copyValues(size_t* values, size_t length) {      //същото като горното но сме му подали size_t пойнтер и size_t
        size_t* copies = new size_t[length];        //заделляме място в хийпа голямо колкото lenght
        for (size_t i = 0; i < length; i++) {//от край до край 
            copies[i] = values[i];          //приравняваме стойностите
        }

        return copies;          //връщаме пойнтера с попълнените данни
    }
};

#endif // RANGE_H

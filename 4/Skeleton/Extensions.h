#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <memory>
#include <stack>
#include <iostream>

#include "InputInterpreter.h"
#include "CalculationEngine.h"
#include "Operation.h"

using namespace std;

class DivisionOperation : public Operation {		//създаваме единия клас който онаследява operation
	std::vector<int> operands;
	int result;
public:

	void addOperand(int operand) override {	
		this->operands.push_back(operand);

		if (this->isCompleted()) {	//ако сме попълнили 2 инта
			this->result = this->operands[0] / this->operands[1];	//делим 2те числа
		}
	}

	bool isCompleted() override {

		return this->operands.size() == 2;		//ако имаме 2 елемента във вектора ще върнем трю
	}

	int getResult() override {	// за да взеем резултата от деленето
		return this->result;
	}
};

class MemorySavedOperation: public Operation {		//добавяме другата функционалност като онаследяваме главния клас
public:
	MemorySavedOperation(std::shared_ptr<std::stack<int>>memory) {		//подаваме шернатия пойнтер
		_memory = memory;
	}

	void addOperand(int operand) override {	
		_memory->push(operand);		//влагаме операндата в стекът който сме сложили

		_isCompleted = true;	//була става верен
	}

	bool isCompleted() override {	//връщаме була
		return _isCompleted;
	}

	int getResult() override {	//вземаме операндата от стека
		return _memory->top();
	}

private:
	std::shared_ptr<stack<int>> _memory;
	bool _isCompleted = false;
};

class MemoryReadOperation : public Operation {	//създаваме 3ти клас който отново да разшири функционалността
public:
	MemoryReadOperation(std::shared_ptr<std::stack<int>>memory) {	// вкарваме шернатият пойнтер към стека
		_memory = memory;
	}

	void addOperand(int operand) override {			//само за защита
		std::cout << "Error, should not be called" << std::endl;
	}

	bool isCompleted() override {	//връщаме трю винаги
		return true;
	}

	int getResult() override {	//вземаме резултата от стекът .
		int result = _memory->top();

		_memory->pop();	//трием последната команда

		return result;
	}

private:
	std::shared_ptr<std::stack<int>>_memory;

};

class ExtendedInputInterpreter : public InputInterpreter {
public:
	ExtendedInputInterpreter(CalculationEngine& engine) : InputInterpreter(engine) {	//викаме конструктора на онаследения клас
		_memory = std::make_shared<std::stack<int>>();
	}

	virtual ~ExtendedInputInterpreter() = default;	//имаш ли виртуална функция - задъллжително виртуален деструктор

	 virtual std::shared_ptr<Operation> getOperation(std::string operation) override {//създаваме ф-я която да връща шернат пойнтер

		shared_ptr<Operation> ptr = InputInterpreter::getOperation(operation);	//създаваме шернат пойнтер който да вика метода от наслледника си

		if (ptr) {		//ако не сочи към nullptr
			return ptr;
		}
		else if (operation == "/") {	//спрямо това каква е операцията
			return std::make_shared<DivisionOperation>();	//създавамме шернат поойнтер обвит в make_shared<>
		}
		else if (operation == "ms") {
			return std::make_shared<MemorySavedOperation>(_memory);		//като вкарваме другият шернат пойнтер в който има stack
		}
		else if (operation == "mr") {
			return std::make_shared<MemoryReadOperation>(_memory);
		}
		
		return std::shared_ptr<Operation>(nullptr);		//а ако няма подходяща операция създаваме празен пойнтер
	}
private:
	std::shared_ptr<std::stack<int>> _memory;
};

std::shared_ptr<InputInterpreter> buildInterpreter(CalculationEngine & engine) {	//създаваме ф-та която да връща шернатия пойнтер
	return std::make_shared<ExtendedInputInterpreter>(engine); //създаваме обект който трябва да е онаследил и разширил функционалността
}


#endif // !EXTENSIONS_H

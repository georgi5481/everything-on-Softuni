#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <memory>
#include <stack>
#include <iostream>

#include "InputInterpreter.h"
#include "CalculationEngine.h"
#include "Operation.h"

using namespace std;

class DivisionOperation : public Operation {		//��������� ������ ���� ����� ���������� operation
	std::vector<int> operands;
	int result;
public:

	void addOperand(int operand) override {	
		this->operands.push_back(operand);

		if (this->isCompleted()) {	//��� ��� ��������� 2 ����
			this->result = this->operands[0] / this->operands[1];	//����� 2�� �����
		}
	}

	bool isCompleted() override {

		return this->operands.size() == 2;		//��� ����� 2 �������� ��� ������� �� ������ ���
	}

	int getResult() override {	// �� �� ����� ��������� �� ��������
		return this->result;
	}
};

class MemorySavedOperation: public Operation {		//�������� ������� �������������� ���� ������������ ������� ����
public:
	MemorySavedOperation(std::shared_ptr<std::stack<int>>memory) {		//�������� �������� �������
		_memory = memory;
	}

	void addOperand(int operand) override {	
		_memory->push(operand);		//������� ���������� � ������ ����� ��� �������

		_isCompleted = true;	//���� ����� �����
	}

	bool isCompleted() override {	//������� ����
		return _isCompleted;
	}

	int getResult() override {	//������� ���������� �� �����
		return _memory->top();
	}

private:
	std::shared_ptr<stack<int>> _memory;
	bool _isCompleted = false;
};

class MemoryReadOperation : public Operation {	//��������� 3�� ���� ����� ������ �� ������� ����������������
public:
	MemoryReadOperation(std::shared_ptr<std::stack<int>>memory) {	// �������� ��������� ������� ��� �����
		_memory = memory;
	}

	void addOperand(int operand) override {			//���� �� ������
		std::cout << "Error, should not be called" << std::endl;
	}

	bool isCompleted() override {	//������� ��� ������
		return true;
	}

	int getResult() override {	//������� ��������� �� ������ .
		int result = _memory->top();

		_memory->pop();	//����� ���������� �������

		return result;
	}

private:
	std::shared_ptr<std::stack<int>>_memory;

};

class ExtendedInputInterpreter : public InputInterpreter {
public:
	ExtendedInputInterpreter(CalculationEngine& engine) : InputInterpreter(engine) {	//������ ������������ �� ����������� ����
		_memory = std::make_shared<std::stack<int>>();
	}

	virtual ~ExtendedInputInterpreter() = default;	//���� �� ��������� ������� - ������������� ��������� ����������

	 virtual std::shared_ptr<Operation> getOperation(std::string operation) override {//��������� �-� ����� �� ����� ������ �������

		shared_ptr<Operation> ptr = InputInterpreter::getOperation(operation);	//��������� ������ ������� ����� �� ���� ������ �� ����������� ��

		if (ptr) {		//��� �� ���� ��� nullptr
			return ptr;
		}
		else if (operation == "/") {	//������ ���� ����� � ����������
			return std::make_shared<DivisionOperation>();	//���������� ������ �������� ����� � make_shared<>
		}
		else if (operation == "ms") {
			return std::make_shared<MemorySavedOperation>(_memory);		//���� �������� ������� ������ ������� � ����� ��� stack
		}
		else if (operation == "mr") {
			return std::make_shared<MemoryReadOperation>(_memory);
		}
		
		return std::shared_ptr<Operation>(nullptr);		//� ��� ���� ��������� �������� ��������� ������ �������
	}
private:
	std::shared_ptr<std::stack<int>> _memory;
};

std::shared_ptr<InputInterpreter> buildInterpreter(CalculationEngine & engine) {	//��������� �-�� ����� �� ����� �������� �������
	return std::make_shared<ExtendedInputInterpreter>(engine); //��������� ����� ����� ������ �� � ��������� � �������� ����������������
}


#endif // !EXTENSIONS_H

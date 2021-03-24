#include <iostream>
#include <sstream>
#include <string>

#include "CalculationEngine.h"
#include "InputInterpreter.h"

#include "Extensions.h"

int main() {
    std::string input;      //създаваме  стринг

    CalculationEngine engine;   //създаваме обект към двигателя 
    std::shared_ptr<InputInterpreter> interpreter = buildInterpreter(engine);   //създаваме си шернат пойнтер към класа 
    while (std::cin >> input) {                                                 //inputinterpreter като сме инициализирали ф-та buildInterpreter
        if (input == "end") {       //след това записваме в стринга докато не прочетем end
            break;
        } else {
            interpreter->interpret(input);      //иначе трупаме в обекта който сме създали
        }
    }

    std::cout << engine.getCurrentResult() << std::endl;        //печатаме резултата

    return 0;
}

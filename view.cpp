#include "view.h"

void View::displayMenu() {
    std::cout << "=========" << std::endl;
    std::cout << " M E N U " << std::endl;
    std::cout << "=========" << std::endl;
    std::cout << "1. Knuth–Morris–Pratt algorithm" << std::endl;
    std::cout << "2. Standart stl algorithm" << std::endl;
    std::cout << "3. Aho–Corasick algorithm" << std::endl;
    std::cout << "0. Quit" << std::endl << std::endl;
}

void View::performAddData() {
    std::cout << "==========" << std::endl;
    std::cout << " H E L L O " << std::endl;
    std::cout << "==========" << std::endl;
    std::cout << "Input a haystack string: " << std::endl << std::endl;
    _haystack = empyString(_haystack);
    std::cout << "Input a needle string: " << std::endl << std::endl;
    _needle = empyString(_needle);
    std::cout << "Input a threshold number: " << std::endl << std::endl;
    _threshold = validationValue(_threshold);
}

std::string View::empyString(std::string giveString) {
    while (!(std::cin >> giveString) || giveString.empty()) {
        std::cin.clear();
        std::cin.ignore(100500, '\n');
        std::cout << "Ohh, your line is empty." << std::endl;
        std::cout << "Try once more!" << std::endl;
    }
    std::cout << std::endl;
    return giveString;
}

size_t View::validationValue(size_t value) {
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(100500, '\n');
        std::cout << "Ohh, your number less zero." << std::endl;
        std::cout << "Try once more!" << std::endl;
    }
    std::cout << std::endl;
    return value;
}

int View::performChoice() {
    int choice;
    std::cout << "Input a menu item digit: ";
    std::cin >> choice;
    return choice;
}

void View::printResultString() {
    std::cout << std::endl;
    std::cout << "=============" << std::endl;
    std::cout << " A N S W E R " << std::endl;
    std::cout << "=============" << std::endl;
    for (auto& string : _resultStrings) {
        std::cout << string << std::endl;
    }
    std::cout << std::endl;
}

void View::startEventLoop() {
    while (true) {
        performAddData();
        displayMenu();
        _controller->setParametr(_haystack, _needle, _threshold);
        switch ((Choice)performChoice()) {
            case KMP:
                try {
                    _resultStrings = _controller->getResultStringsKMP();
                } catch (std::out_of_range const& ex) {
                    std::cout << ex.what() << std::endl;
                }
                break;
            case STL:
                try {
                    _resultStrings = _controller->getResultStringsSTL();
                } catch (std::out_of_range const& ex) {
                    std::cout << ex.what() << std::endl;
                }
                break;
            case AC:
                try {
                    _resultStrings = _controller->getResultStringsAC();
                } catch (std::out_of_range const& ex) {
                    std::cout << ex.what() << std::endl;
                }
                break;
            case EXIT:
                exit(1);
            default:
                std::cout << "Wrong menu item number!";
                continue;
        }
        printResultString();
    }
}

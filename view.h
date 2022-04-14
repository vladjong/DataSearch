#pragma once
#include "controller.h"

enum Choice {
    KMP = 1,
    STL = 2,
    AC = 3,
    EXIT = 0,
};

class View {
 private:
    Controller *_controller;
    std::string _haystack;
    std::string _needle;
    size_t _threshold;
    std::vector<std::string> _resultStrings;

 public:
    explicit View(Controller *controller) : _controller(controller) {}
    ~View() {}

    void displayMenu();
    void startEventLoop();
    void performAddData();
    int performChoice();
    std::string empyString(std::string);
    size_t validationValue(size_t);
    void printResultString();
    void setParametr(std::string haystack, std::string needle, size_t threshould) {
        _controller->setParametr(haystack, needle, threshould);
    }
};

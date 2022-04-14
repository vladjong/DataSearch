#pragma once
#include "model.h"

class Controller {
 private:
    Model *_model;

 public:
    explicit Controller(Model *model) : _model(model) {}

    std::vector<std::string> getResultStringsSTL() { return _model->getResultStringsSTL(); }
    std::vector<std::string> getResultStringsAC() { return _model->getResultStringsAC(); }
    std::vector<std::string> getResultStringsKMP() { return _model->getResultStringsKMP(); }
    void setParametr(std::string haystack, std::string needle, size_t threshould) {
        _model->setParametr(haystack, needle, threshould);
    }
};

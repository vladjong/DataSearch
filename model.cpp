#include "model.h"

AhoCorasickAlgorithm::~AhoCorasickAlgorithm() {
    std::queue<Bor*> queueTemp;
    for (std::map<char, Bor*>::const_iterator iterator = _root._links.begin();
         iterator != _root._links.end(); ++iterator)
        queueTemp.push(iterator->second);
    while (!queueTemp.empty()) {
        Bor* currentNode = queueTemp.front();
        queueTemp.pop();
        for (std::map<char, Bor*>::const_iterator iterator = currentNode->_links.begin();
             iterator != currentNode->_links.end(); ++iterator)
            queueTemp.push(iterator->second);
        delete currentNode;
    }
}

void AhoCorasickAlgorithm::addString(std::string giveString, size_t index) {
    Bor* node = &_root;
    for (const char* s = giveString.c_str(); *s; ++s) {
        std::map<char, Bor*>::iterator iterator = node->_links.find(*s);
        if (iterator != node->_links.end()) {
            node = iterator->second;
        } else {
            Bor* tempNode = new Bor;
            node->_links[*s] = tempNode;
            node = tempNode;
        }
    }
    node->_out = _words.size();
    _words.push_back(std::make_pair(giveString, index));
}

void AhoCorasickAlgorithm::init() {
    _root._checkError = &_root;
    std::queue<Bor*> queueTemp;
    queueTemp.push(&_root);
    while (!queueTemp.empty()) {
        Bor* current_node = queueTemp.front();
        queueTemp.pop();
        for (std::map<char, Bor*>::const_iterator iterator = current_node->_links.begin();
             iterator != current_node->_links.end(); ++iterator) {
            Bor* child = iterator->second;
            char symb = iterator->first;
            queueTemp.push(child);
            Bor* parent_fail = current_node->_checkError;
            while (true) {
                std::map<char, Bor*>::const_iterator iteratorTemp = parent_fail->_links.find(symb);
                if (iteratorTemp != parent_fail->_links.end()) {
                    child->_checkError = iteratorTemp->second != child ? iteratorTemp->second : &_root;
                    if (child->_out < 0) child->_out = child->_checkError->_out;
                    break;
                }
                if (parent_fail == &_root) {
                    child->_checkError = &_root;
                    break;
                } else {
                    parent_fail = parent_fail->_checkError;
                }
            }
        }
    }
}

void AhoCorasickAlgorithm::search(std::string giveString) {
    Bor* current_node = &_root;
    for (size_t pos = 1, i = 0; i < giveString.length(); ++i, ++pos) {
        std::map<char, Bor*>::const_iterator iter = current_node->_links.find(giveString[i]);
        while (iter == current_node->_links.end()) {
            current_node = current_node->_checkError;
            iter = current_node->_links.find(giveString[i]);
            if (current_node == current_node->_checkError) break;
        }
        if (iter != current_node->_links.end()) {
            current_node = iter->second;
            if (current_node->_out >= 0) {
                size_t substringLength = _words[current_node->_out].first.length();
                size_t position = _words[current_node->_out].second;
                fillData(substringLength, pos - substringLength, position, _lastSequenceLength);
                giveString.erase(pos - substringLength, substringLength);
                _lastSequenceLength += substringLength;
            }
        }
    }
}

void AhoCorasickAlgorithm::fiilTree(std::multimap<size_t, std::string> kitSubstring) {
    for (auto& index : kitSubstring) {
        addString(index.second, index.first);
    }
}

void AhoCorasickAlgorithm::fillData(size_t substringLength, size_t start, size_t end,
                                    size_t _lastSequenceLength) {
    std::string resultString = "sequence of length = " + std::to_string(substringLength);
    resultString += " found at haystack offset " + std::to_string(start + _lastSequenceLength);
    resultString += ", needle offset " + std::to_string(end);
    _resultStrings.push_back(resultString);
}

void KnuthMorrisPrattAlgorithm::KMP(std::multimap<size_t, std::string> kitSubstring) {
    _haystackLength = _haystack.length();
    _needleLength = _needle.length();
    validationSubstring();
    for (auto& index : kitSubstring) {
        auto substring = algorithmKMP(index.second);
        printResultKMP(index.second, substring, index.first);
    }
}

void Model::enumerationSubstrings() {
    size_t lastPoint = _needle.length();
    for (size_t firstPoint = 0; firstPoint <= lastPoint - _threshould; firstPoint++) {
        for (size_t leftShift = lastPoint - firstPoint; leftShift >= _threshould; leftShift--) {
            _kitSubstring.insert({firstPoint, _needle.substr(firstPoint, leftShift)});
        }
    }
}

std::vector<size_t> KnuthMorrisPrattAlgorithm::algorithmKMP(std::string needle) {
    size_t needleLength = needle.length();
    std::vector<size_t> substring(needleLength + 1);
    for (size_t i = 0; i < needleLength + 1; i++) {
        substring[i] = 0;
    }
    for (size_t i = 1; i < needleLength; i++) {
        size_t j = substring[i + 1];
        while (j > 0 && needle[j] != needle[i]) {
            j = substring[j];
        }
        if (j > 0 || needle[j] == needle[i]) {
            substring[i + 1] = j + 1;
        }
    }
    return substring;
}

void KnuthMorrisPrattAlgorithm::printResultKMP(std::string needle, std::vector<size_t> substring,
                                               size_t index) {
    size_t needleLength = needle.length();
    for (size_t i = 0, j = 0; i < _haystackLength; i++) {
        if (_haystack[i] == needle[j]) {
            if (++j == needleLength) {
                size_t firstIndex = i - j + 1;
                _resultStrings.push_back(formString(needleLength, firstIndex, index, _lastSequenceLength));
                _haystack.erase(firstIndex, needleLength);
                _lastSequenceLength += needleLength;
            }
        } else if (j > 0) {
            j = substring[j];
            i--;
        }
    }
}

std::string KnuthMorrisPrattAlgorithm::formString(size_t needleLength, size_t firstIndex, size_t index,
                                                  size_t _lastSequenceLength) {
    std::vector<std::string> resultVector;
    std::string resultString = "sequence of length = " + std::to_string(needleLength);
    resultString += " found at haystack offset " + std::to_string(firstIndex + _lastSequenceLength);
    resultString += ", needle offset " + std::to_string(index);
    return resultString;
}

void KnuthMorrisPrattAlgorithm::validationSubstring() {
    if (_needleLength == 0) {
        std::out_of_range("The needle string empty");
    }
    if (_haystackLength < _needleLength) {
        std::out_of_range("The needle string more than haystack string");
    }
}

void STLAlgorithm::stlFind(std::multimap<size_t, std::string> kitSubstring) {
    _haystackLength = _haystack.length();
    _needleLength = _needle.length();
    KnuthMorrisPrattAlgorithm::validationSubstring();
    for (auto& index : kitSubstring) {
        std::string substring = index.second;
        size_t sequenceLength = substring.length();
        for (int i = _haystack.find(substring); i != std::string::npos;
             i = _haystack.find(substring, i + 1)) {
            _haystack.erase(i, sequenceLength);
            _resultStrings.push_back(
                KnuthMorrisPrattAlgorithm::formString(sequenceLength, i, index.first, _lastSequenceLength));
            _lastSequenceLength += sequenceLength;
        }
    }
}

Model::~Model() {
    if (_knuthMorrisPrattAlgorithm != nullptr) {
        delete _knuthMorrisPrattAlgorithm;
    }
    if (_ahoCorasickAlgorithm != nullptr) {
        delete _ahoCorasickAlgorithm;
    }
}

void Model::setParametr(std::string haystack, std::string needle, size_t threshould) {
    _haystack = haystack;
    _needle = needle;
    _threshould = threshould;
}

std::vector<std::string> Model::getResultStringsKMP() {
    _knuthMorrisPrattAlgorithm = new KnuthMorrisPrattAlgorithm(_haystack, _needle, _threshould);
    enumerationSubstrings();
    _knuthMorrisPrattAlgorithm->KMP(_kitSubstring);
    return _knuthMorrisPrattAlgorithm->getResultStrings();
}

std::vector<std::string> Model::getResultStringsAC() {
    _ahoCorasickAlgorithm = new AhoCorasickAlgorithm();
    enumerationSubstrings();
    _ahoCorasickAlgorithm->fiilTree(_kitSubstring);
    _ahoCorasickAlgorithm->init();
    _ahoCorasickAlgorithm->search(_haystack.c_str());
    return _ahoCorasickAlgorithm->getResultStrings();
}

std::vector<std::string> Model::getResultStringsSTL() {
    _stlAlgorithm = new STLAlgorithm(_haystack, _needle, _threshould);
    enumerationSubstrings();
    _stlAlgorithm->stlFind(_kitSubstring);
    return _stlAlgorithm->getResultStrings();
}

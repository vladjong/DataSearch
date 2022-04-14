#pragma once

#include <string.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

class AhoCorasickAlgorithm {
 private:
    struct Bor {
        Bor() : _checkError(nullptr), _out(-1) {}
        std::map<char, Bor *> _links;
        Bor *_checkError;
        int _out;
    };
    Bor _root;
    size_t _lastSequenceLength;
    std::vector<std::pair<std::string, size_t>> _words;
    std::vector<std::string> _resultStrings;

 public:
    ~AhoCorasickAlgorithm();
    void fiilTree(std::multimap<size_t, std::string>);
    void addString(std::string, size_t);
    void init();
    void search(std::string);
    void fillData(size_t, size_t, size_t, size_t);
    std::vector<std::string> getResultStrings() { return _resultStrings; }
};

class KnuthMorrisPrattAlgorithm {
 protected:
    std::string _haystack;
    std::string _needle;
    size_t _threshould;
    size_t _haystackLength;
    size_t _needleLength;
    size_t _lastSequenceLength;
    std::vector<std::string> _resultStrings;

    std::vector<size_t> algorithmKMP(std::string);
    std::string formString(size_t, size_t, size_t, size_t);
    void printResultKMP(std::string, std::vector<size_t>, size_t);
    void validationSubstring();

 public:
    KnuthMorrisPrattAlgorithm() {}
    KnuthMorrisPrattAlgorithm(std::string haystack, std::string needle, size_t threshould)
        : _haystack(haystack), _needle(needle), _threshould(threshould) {}
    void KMP(std::multimap<size_t, std::string>);
    std::vector<std::string> getResultStrings() { return _resultStrings; }
};

class STLAlgorithm : protected KnuthMorrisPrattAlgorithm {
 private:
    std::string _haystack;
    std::string _needle;
    size_t _threshould;
    size_t _haystackLength;
    size_t _needleLength;
    size_t _lastSequenceLength;
    std::vector<std::string> _resultStrings;

 public:
    STLAlgorithm(std::string haystack, std::string needle, size_t threshould)
        : _haystack(haystack), _needle(needle), _threshould(threshould) {}
    void stlFind(std::multimap<size_t, std::string>);
    std::vector<std::string> getResultStrings() { return _resultStrings; }
};

class Model {
 private:
    AhoCorasickAlgorithm *_ahoCorasickAlgorithm;
    KnuthMorrisPrattAlgorithm *_knuthMorrisPrattAlgorithm;
    STLAlgorithm *_stlAlgorithm;
    std::multimap<size_t, std::string> _kitSubstring;
    std::string _haystack;
    std::string _needle;
    size_t _threshould;

    void enumerationSubstrings();

 public:
    Model() {}
    ~Model();
    void setParametr(std::string haystack, std::string needle, size_t threshould);
    std::vector<std::string> getResultStringsKMP();
    std::vector<std::string> getResultStringsAC();
    std::vector<std::string> getResultStringsSTL();
};

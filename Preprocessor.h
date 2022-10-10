#pragma once
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <iostream>
class Preprocessor
{
public:
    Preprocessor();
    void PreProcess(const std::string&);
private:
    typedef void (Preprocessor::*func) (const std::string&);
    std::vector<std::string> split(const std::string& str, const std::string& spliter);
    void include(const std::string&);
    void define(const std::string&);
    void replace(std::string&);
    void undef(const std::string&);
    void ifdef(const std::string&);
    void ifndef(const std::string&);
    void init();
private:
    std::fstream fin;
    std::fstream fout;
    bool flag;
    std::map<std::string, func> inst;
    std::map<std::string, std::string> defs;
};
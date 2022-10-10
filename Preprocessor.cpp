#include "Preprocessor.h"
void Preprocessor::init()
{
    flag = true;
    inst["#include"] = &Preprocessor::include;
    inst["#define"] = &Preprocessor::define;
    inst["#undef"] = &Preprocessor::undef;
    inst["#ifdef"] = &Preprocessor::ifdef;
    inst["#ifndef"] = &Preprocessor::ifndef;
}

Preprocessor::Preprocessor()
{
    init();
}

void Preprocessor::PreProcess(const std::string& filename)
{
    fin.open(filename);
    fout.open("output.txt");
    std::string line = "";
    std::string dst = " ";
    if (fin.is_open() && fout.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, line);
            auto vec = split(line, dst);
            if (vec[0] == "#endif")
            {
                fout << std::endl;
                flag = true;
                continue;
            }
            if (inst.find(vec[0]) != inst.end())
            {
                (this->*inst[vec[0]])(vec[1] + " " + vec[2]);
            }
            else 
            {
                if (flag)
                {
                    replace(line);
                    fout << line << std::endl;
                }
            }
        }
    }
    fin.close();
    fout.close();
}
void Preprocessor::ifndef(const std::string& line)
{
    fout << std::endl;
    auto vec = split(line, " ");
    if (defs.find(vec[0]) != defs.end())
    {
        flag = false;
        return;
    }
    flag = true;
}
void Preprocessor::ifdef(const std::string& line)
{
    fout << std::endl;
    auto vec = split(line, " ");
    if (defs.find(vec[0]) != defs.end())
    {
        flag = true;
        return;
    }
    flag = false;
}
void Preprocessor::include(const std::string& filename)
{
    std::string path = "";
    std::string dst = " ";

    for (int i = 1; filename[i] != static_cast<char>(34); ++i)
    {
        path += filename[i];
    }
    std::fstream fine;
    std::string line;
    fine.open(path);
    if (fine.is_open())
    {
        while (!fine.eof())
        {
            getline(fine, line);
            auto vec = split(line, dst);
            if (inst.find(vec[0]) != inst.end())
            {
                (this->*inst[vec[0]]) (vec[1] + " " + vec[2]);
            }
            
            else
            {
                fout << line << std::endl;
            }
        }
}
}
std::vector<std::string> Preprocessor::split(const std::string& str, const std::string& spliter) {
    std::vector<std::string> nstr = {};
    std::string tstr = {};
    for (int i = 0; i < str.size(); ++i) {
        if (spliter.find(str[i]) != std::string::npos) {
            if (tstr != "") {
                nstr.push_back(tstr);
                tstr.clear();
                continue;
            }
            continue;
        }
        tstr.push_back(str[i]);
    }
    nstr.push_back(tstr);
    return nstr;
}
void Preprocessor::define(const std::string& dst)
{
    fout << std::endl;
    auto vec = split(dst, " ");
    defs[vec[0]] = vec[1];
}

void Preprocessor::replace(std::string& line)
{
    for (auto it : defs) {
        if (line.find(it.first) != std::string::npos) {
            int pos = 0;
            while ((pos = line.find(it.first, pos)) != -1) {
                line.erase(line.begin() + line.find(it.first),line.begin() + line.find(it.first) + it.first.size());
                line.insert(pos, it.second);
            }
        }
    }
}
void Preprocessor::undef(const std::string& line)
{
    fout << std::endl;
    std::string str = line;
    if (str.find(' ') != std::string::npos)
    {
        str.erase(str.find(' '));
    }
    defs.erase(str);
}

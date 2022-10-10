#include "Preprocessor.h"
#define X 10
int main(int argc, char **argv)
{
    Preprocessor proc;
    if (argc == 2) 
    {
        proc.PreProcess(argv[1]);
    }
    else
    {
        throw std::invalid_argument("Wrong number of arguments");
    }
    

}
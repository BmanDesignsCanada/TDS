#ifndef TDS_H
#define TDS_H
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

class TDS
{
    public:
        TDS(const std::string& filename);
        char* get(const std::string& file, unsigned int &length);
    private:
        unsigned int files;
        std::vector<std::string> fileNames;
        std::vector<char*> fileData;
        std::vector<unsigned int> fileLength;
};
#endif

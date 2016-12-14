#include <string>
#include <iostream>
#include <fstream>
#include <vector>

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

int main(int argc, char* argv[])
{
    if(argc < 3){
        std::cout << "Missing Arguments" << std::endl;
        return 1;
    }
    std::string output = argv[1];
    output = output + ".tds";
    std::cout << output << std::endl;
    unsigned int files = argc - 2;
    std::cout << "Preparing to pack " << files << " files" << std::endl;
    std::fstream outputFile (output, std::fstream::out | std::ios::binary);
    outputFile.write ((char *)&files, sizeof(files));
    for(int i = 2; i < argc; i++)
    {
        std::cout << "Packing: " << argv[i] << std::endl;
        std::string name = argv[i];
        unsigned int name_length = sizeof(char) * name.length();
        outputFile.write((char *)&name_length,sizeof(name_length));
        outputFile.write(name.c_str(),name_length);
        unsigned int fs = filesize(name.c_str());
        std::ifstream input( name , std::ios::binary);
        outputFile.write((char *)&fs,sizeof(unsigned int));
        for(unsigned int x = 0; x < fs; x++)
        {
            char byte;
            input.read(&byte,1);
            outputFile.write(&byte,1);
        }
    }
    outputFile.close();
}

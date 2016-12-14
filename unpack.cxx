#include <fstream>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc < 3){
        std::cout << "Missing Arguments" << std::endl;
        return 1;
    }
    std::string input   = argv[1];
    std::string file    = argv[2];
    bool list = false;
    if(file == "--list")
    {
        list = true;
    }
    bool out = false;
    std::string output;
    if(argc == 4){
        output = argv[3];
        out = true;
    }
    std::ifstream f( input , std::ios::binary);
    unsigned int files;
    f.read((char *)&files,sizeof(unsigned int));
    for (unsigned int i = 0; i < files; i++){
        unsigned int name_length;
        f.read((char *)&name_length,sizeof(unsigned int));
        char* temp = new char[name_length+1];
        f.read(temp,name_length);
        temp[name_length] = '\0';
        std::string name = temp;
        delete [] temp;
        unsigned int file_length;
        f.read((char *)&file_length,sizeof(unsigned int));
        if(list)
        {
            std::cout << name << ": " << file_length << std::endl;
            f.seekg(file_length,std::ios_base::cur);
        }
        else
        {
            if(name == file)
            {
                char* data = new char[file_length];
                f.read(data,file_length);
                if(out)
                {
                    std::ofstream outputFile (output, std::ios::binary);
                    outputFile.write(data,file_length);
                    outputFile.close();
                }
                else
                {
                    fwrite(data,sizeof(char),file_length,stdout);
                    fclose (stdout);
                }
                f.close();
                return 0;
            }
            else
            {
                f.seekg(file_length,std::ios_base::cur);
            }
        }

    }
    f.close();
    return 1;
}

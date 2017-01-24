#include "tds.h"

TDS::TDS(const std::string& filename)
{
    //Open the TDS
    std::ifstream f(filename, std::ifstream::binary);
    //Get the number of files stored in the TDS
    f.read((char *)&files,sizeof(unsigned int));
    //Iterate over all files
    for (unsigned int i = 0; i < files; i++)
    {
        //Get the name of the file
        unsigned int name_length;
        f.read((char *)&name_length,sizeof(unsigned int));
        char* temp = new char[name_length+1];
        f.read(temp,name_length);
        temp[name_length] = '\0';
        std::string name = temp;
        fileNames.push_back(name);
        delete [] temp;
        //Read the file into ram
        unsigned int file_length;
        f.read((char *)&file_length,sizeof(unsigned int));
        fileLength.push_back(file_length);
        char* data = new char[file_length];
        f.read(data,file_length);
        //Store data in the vector
        fileData.push_back(data);
    }
    f.close();
}

char* TDS::get(const std::string& file, unsigned int &length)
{
    for (int i = 0; i<fileNames.size(); i++)
    {
        if (fileNames[i] == file)
        {
            length = fileLength[i];
            return fileData[i];
        }
    }
}

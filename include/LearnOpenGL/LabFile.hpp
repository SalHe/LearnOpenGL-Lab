#ifndef ___LEARN_OPENGL_LABFILE_H___
#define ___LEARN_OPENGL_LABFILE_H___

#include <string>

class LabFile
{
public:
    static std::string getFilePath(std::string filename)
    {  
        return "../../../" + filename;
    }
};

#endif
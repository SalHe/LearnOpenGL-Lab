#include <string>

class LabFile
{
public:
    static std::string getFilePath(std::string filename)
    {  
        return "../../../" + filename;
    }
};
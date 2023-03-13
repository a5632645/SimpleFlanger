/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== TODO.txt ==================
static const unsigned char temp_binary_data_0[] =
{ 49,46,233,135,141,229,136,182,71,85,73,239,188,140,230,183,187,229,138,160,231,177,187,228,188,188,228,191,161,229,143,183,229,164,132,231,144,134,228,185,166,228,184,138,231,154,132,231,172,166,229,143,183,239,188,159,13,10,50,46,231,167,187,233,153,
164,228,184,141,229,191,133,232,166,129,231,154,132,230,179,162,229,189,162,229,138,159,232,131,189,13,10,51,46,230,183,187,229,138,160,76,70,79,44,69,78,86,231,154,132,109,105,100,105,232,167,166,229,143,145,13,10,52,46,229,174,140,229,150,132,76,70,
79,44,69,78,86,44,77,65,78,85,65,76,13,10,53,46,228,189,191,231,148,168,65,80,86,84,83,229,146,140,231,187,145,229,174,154,229,153,168,0,0 };

const char* TODO_txt = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0xe17ebef7:  numBytes = 171; return TODO_txt;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "TODO_txt"
};

const char* originalFilenames[] =
{
    "TODO.txt"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}

#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring file)
{
    size_t index = file.find_last_of('.');
    
    return file.substr(index + 1, file.length());
}

#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring file)
{
    size_t index = file.find_last_of('.');

    return file.substr(index + 1, file.length());
}

string Utility::ToString(wstring str)
{
    string temp;

    temp.assign(str.begin(), str.end());

    return temp;
}

wstring Utility::ToWString(string str)
{
    wstring temp;

    temp.assign(str.begin(), str.end());

    return temp;
}

bool Utility::StartsWith(string str, string start)
{
    string result = str.substr(0, start.size());

    return result == start;
}

bool Utility::StartsWith(wstring str, wstring start)
{
    wstring result = str.substr(0, start.size());

    return result == start;
}


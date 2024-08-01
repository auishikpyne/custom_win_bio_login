//utilities.cpp
#include "pch.h"
#include "Utilities.h"
#include <sstream>

// Definition of ToWString function
std::wstring ToWString(long value)
{
    std::wostringstream woss;
    woss << value;
    return woss.str();
}

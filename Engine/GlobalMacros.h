#pragma once

//DEBUG WINDOW OUTPUT MACRO
#include <iostream>
#include <sstream>
#define DBOUT( s )            \
{                             \
std::wostringstream os_;    \
os_ << s;                   \
OutputDebugStringW( os_.str().c_str() );  \
}
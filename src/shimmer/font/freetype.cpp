#include "freetype.hpp"

// Source: http://stackoverflow.com/questions/31161284/how-can-i-get-the-corresponding-error-string-from-an-ft-error-code
std::string shimmer::freetype_string_from ( FT_Error code )
{
#undef __FTERRORS_H__
#define FT_ERROR_START_LIST     switch (code) {
#define FT_ERRORDEF( e, v, s )  case e: return s;
#define FT_ERROR_END_LIST       }
#include FT_ERRORS_H
        return "unknown";
}

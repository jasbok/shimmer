#include "catch.hpp"
#include "font/font_loader.hpp"

using namespace shimmer;
TEST_CASE ( "Basic font loading." )
{
        font_loader font_loader;
        font_face face = std::move ( *font_loader.load ( "../../../fonts/xolonium/ttf/Xolonium-Regular.ttf", 12 ) );
        CHECK ( std::string ( face->family_name ) == std::string ( "Xolonium" ) );
        CHECK ( face['a'] != nullptr );
}

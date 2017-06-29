#include "catch.hpp"
#include "shimmer.hpp"

using namespace shimmer;
TEST_CASE ( "Mouse warp function." )
{
        class::shimmer shim;
        shim.video()->resize ( {320, 200}, {320, 200} );
        coordinates<> coords = {8, 8};

        SECTION ( "With source == target size." ) {
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 8, 8 ) );
        }

        SECTION ( "After window resize." ) {
                shim.video()->resize_video ( {640, 400} );
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 4, 4 ) );
        }

        SECTION ( "After target resize." ) {
                shim.video()->resize_video ( {1280, 800} );
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 2, 2 ) );
        }

        SECTION ( "After source and target resize." ) {
                shim.video()->resize ( {100, 200}, {200, 800} );
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 2, 4 ) );
        }

        SECTION ( "After multiple target resizes." ) {
                shim.video()->resize_video ( {100, 200} );
                shim.video()->resize_video ( {1000, 480} );
                shim.video()->resize_video ( {320, 200} );
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 8, 8 ) );
        }
}

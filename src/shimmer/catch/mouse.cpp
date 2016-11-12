#include "catch.hpp"
#include "../shimmer.hpp"

using namespace shimmer;
TEST_CASE ( "Mouse warp function." )
{
        class::shimmer shim;
        shim.video_api()->source ( {320, 200} );
        shim.video_api()->target ( {320, 200} );
        coordinates<> coords = {8, 8};

        SECTION ( "With source == target size." ) {
                shim.mouse_api()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 8, 8 ) );
        }

        SECTION ( "After window resize." ) {
                shim.window_api()->resize ( {640, 400} );
                shim.mouse_api()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 4, 4 ) );
        }

        SECTION ( "After target resize." ) {
                shim.video_api()->target ( {1280, 800} );
                shim.mouse_api()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 2, 2 ) );
        }

        SECTION ( "After source and target resize." ) {
                shim.video_api()->source ( {100, 200} );
                shim.video_api()->target ( {200, 800} );
                shim.mouse_api()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 4, 2 ) );
        }

        SECTION ( "After multiple target resizes." ) {
                shim.video_api()->target ( {100, 200} );
                shim.video_api()->target ( {1000, 480} );
                shim.video_api()->target ( {320, 200} );
                shim.mouse_api()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 8, 8 ) );
        }
}

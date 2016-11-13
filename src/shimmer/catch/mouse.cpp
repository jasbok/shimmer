#include "catch.hpp"
#include "shimmer.hpp"

using namespace shimmer;
TEST_CASE ( "Mouse warp function." )
{
        class::shimmer shim;
        shim.video()->source_dims ( {320, 200} );
        shim.video()->target_dims ( {320, 200} );
        coordinates<> coords = {8, 8};

        SECTION ( "With source == target size." ) {
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 8, 8 ) );
        }

        SECTION ( "After window resize." ) {
                shim.window()->resize ( {640, 400} );
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 4, 4 ) );
        }

        SECTION ( "After target resize." ) {
                shim.video()->target_dims ( {1280, 800} );
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 2, 2 ) );
        }

        SECTION ( "After source and target resize." ) {
                shim.video()->source_dims ( {100, 200} );
                shim.video()->target_dims ( {200, 800} );
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 4, 2 ) );
        }

        SECTION ( "After multiple target resizes." ) {
                shim.video()->target_dims ( {100, 200} );
                shim.video()->target_dims ( {1000, 480} );
                shim.video()->target_dims ( {320, 200} );
                shim.mouse()->transform ( &coords.x, &coords.y );
                CHECK ( coords == coordinates<> ( 8, 8 ) );
        }
}

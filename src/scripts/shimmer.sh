#!/bin/bash

SHIMMER_LIBS="/usr/local/libshimmer"
APP=
SHIM=

for ARG in $@
do
    BIN=$(type -p $ARG )

    if [ -f "$BIN" ]
    then
        echo "shimmer.sh: Found $ARG at $BIN"
        LDD=$(ldd $BIN)

        SDL=$(echo $LDD | grep libSDL-1.2.so | wc -l)
        SDL2=$(echo $LDD | grep libSDL2.so | wc -l)

        if [[ $SDL == 1 ]]
        then
            APP=$ARG
            SHIM="$SHIMMER_LIBS/libshimmer_sdl.so"
            break
        elif [[ $SDL2 == 1 ]]
        then
            APP=$ARG
            SHIM="$SHIMMER_LIBS/libshimmer_sdl2.so"
            break
        fi
    fi
done

if [ -n "$SHIM" ]
then
    echo "shimmer.sh: Using $SHIM with $APP"
    LD_PRELOAD=$SHIM exec $@
else
    echo "shimmer.sh: Could not determine the correct shim for: $@"
fi

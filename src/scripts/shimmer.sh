#!/bin/bash

LONGOPTS="sdl,sdl2"

SHIMMER_LIBS="/usr/local/libshimmer"
SHIM_SDL="$SHIMMER_LIBS/libshimmer_sdl.so"
SHIM_SDL2="$SHIMMER_LIBS/libshimmer_sdl2.so"

args=$(getopt -l $LONGOPTS -- "$@")
eval set -- "$args"
while [ $# -ge 1 ]; do
        case "$1" in
                --)
                    shift
                    break
                   ;;
                --sdl)
                        SHIM="$SHIM_SDL"
                        shift
                        ;;
                -sdl2)
                        SHIM="$SHIM_SDL2"
                        shift
                        ;;
        esac
        shift
done

if [ -n "$SHIM" ]
then
    for ARG in $@
    do
        BIN=$(type -p $ARG )

        if [ -f "$BIN" ]
        then
            echo "shimmer.sh: Found $ARG at $BIN"
            LDD=$(ldd $BIN)

            if [[ $(echo $LDD | grep libSDL-1.2.so | wc -l) == 1 ]]
            then
                APP=$ARG
                SHIM="$SHIMMER_LIBS/libshimmer_sdl.so"
                break
            elif [[ $(echo $LDD | grep libSDL2.so | wc -l) == 1 ]]
            then
                APP=$ARG
                SHIM="$SHIMMER_LIBS/libshimmer_sdl2.so"
                break
            fi
        fi
    done
fi

if [ -n "$SHIM" ]
then
    echo "shimmer.sh: Using $SHIM with $APP"
    LD_PRELOAD=$SHIM exec $@
else
    echo "shimmer.sh: Could not determine the correct shim for: $@"
fi

#!/bin/sh

DIR=$(basename $(pwd))

if [ "$DIR" != "build" ]; then
    cd build
fi

for t in *test; do
    echo ":: Running test $t"
    ./$t
done
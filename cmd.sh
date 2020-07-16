#! /bin/sh

run() {
    echo "> $*"
    $*
}

if [ "$1" = "build" ]; then
    run sw -config r --build-name rayon build -output-dir bin;
elif [ "$1" = "debug" ]; then
    run sw -config d --build-name rayon build -output-dir .sw/out/debug
elif [ "$1" = "compdb" ]; then
    run sw --build-name rayon generate -g compdb
else
    echo "Command not found: $1"
    echo "Try build, debug or compdb"
fi
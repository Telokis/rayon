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
elif [ "$1" = "run" ]; then
    if [ "$2" = "cli" ]; then
        ./bin/rayon.$2-0.0.1.exe  "-w" "1024" "-j" "8" "-h" "1024" "-o" "./out.png" "./files/scenes/above.yon"
    else
        ./bin/rayon.$2-0.0.1.exe $*
    fi
else
    echo "Command not found: $1"
    echo "Try build, debug, run or compdb"
fi
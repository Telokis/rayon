#! /bin/sh

run() {
    echo "> $*"
    $*
}

if [ "$1" = "build" ]; then
    if [ "$#" -eq 1 ]; then
        run sw -j8 -config r --build-name rayon build -output-dir bin
    else
        run sw -j8 -config r --build-name rayon build -output-dir bin -target rayon.$2-0.0.1
    fi
elif [ "$1" = "debug" ]; then
    if [ "$#" -eq 1 ]; then
        run sw -j8 -config d --build-name rayon build -output-dir .sw/out/debug
    else
        run sw -j8 -config d --build-name rayon build -output-dir .sw/out/debug -target rayon.$2-0.0.1
    fi
elif [ "$1" = "generate" ]; then
    run sw -j8 -config r --build-name rayon generate
elif [ "$1" = "compdb" ]; then
    run sw -j8 --build-name rayon generate -g compdb
elif [ "$1" = "run" ]; then
    if [ "$2" = "cli" ]; then
        run ./bin/rayon.$2-0.0.1.exe  "-w" "512" "-j" "2" "-h" "512" "-o" "./out.png" "./files/scenes/sunset.yon"
    else
        run ./bin/rayon.$2-0.0.1.exe "${@:3}"
    fi
else
    echo "Command not found: $1"
    echo "Try build, debug, run, generate or compdb"
fi
#!/bin/sh

filename="./Include/Version.hh"
major=$(cat $filename | tr -d '\n' | sed -r 's/.*RAYON_MAJOR_VERSION ([0-9]+).*/\1/')
minor=$(cat $filename | tr -d '\n' | sed -r 's/.*RAYON_MINOR_VERSION ([0-9]+).*/\1/')
build=$(git rev-list HEAD | wc -l | tr -d '\n' | tr -d ' ')
chash=$(git rev-parse --short HEAD | tr -d '\n' | tr -d ' ')
fullversion="$major.$minor.$build-$chash"

echo $fullversion

exit 0

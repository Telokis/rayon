#!/bin/bash

filename="./Include/Version.hh"
major=$(cat $filename | tr -d '\n' | sed -r 's/.*RAYON_MAJOR_VERSION ([0-9]+).*/\1/')
minor=$(cat $filename | tr -d '\n' | sed -r 's/.*RAYON_MINOR_VERSION ([0-9]+).*/\1/')

tagname="v$major.$minor.0"

diffval=$(git diff HEAD^ HEAD)
if (echo "$diffval" | grep -q "+"$'\x23'"define RAYON_MAJOR_VERSION") || (echo "$diffval" | grep -q "+"$'\x23'"define RAYON_MINOR_VERSION") ; then
	echo "major or minor version changed ! Creating tag $tagname !"
	git tag -a "$tagname" -m "Auto tagging $tagname"
fi

exit 0

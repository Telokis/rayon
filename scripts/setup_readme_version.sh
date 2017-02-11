#!/bin/sh

filename="./README.md"
major=$(cat Include/Version.hh | tr -d '\n' | sed -r 's/.*RAYON_MAJOR_VERSION ([0-9]+).*/\1/')
minor=$(cat Include/Version.hh | tr -d '\n' | sed -r 's/.*RAYON_MINOR_VERSION ([0-9]+).*/\1/')
tagname=$(git describe --abbrev=0 --tags 2> /dev/null)
if (( $? )) ; then
	build=$(git rev-list HEAD | wc -l | tr -d '\n' | tr -d ' ')
else
	build=$(git rev-list  "$tagname..HEAD" --count)
fi
build=$(($build+1))

diffval=$(git diff HEAD^)
if (echo "$diffval" | grep -q "+"$'\x23'"define RAYON_MAJOR_VERSION") || (echo "$diffval" | grep -q "+"$'\x23'"define RAYON_MINOR_VERSION") ; then
	build="0"
fi

build="${build}_"
sed -i "s/_Current repository version : .*_/_Current repository version : v$major.$minor.$build/" README.md
git add README.md

exit 0

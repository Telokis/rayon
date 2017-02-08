#!/bin/sh

filename="./Source/Version.cpp"
major=$(cat Include/Version.hh | tr -d '\n' | sed -r 's/.*RAYON_MAJOR_VERSION ([0-9]+).*/\1/')
minor=$(cat Include/Version.hh | tr -d '\n' | sed -r 's/.*RAYON_MINOR_VERSION ([0-9]+).*/\1/')
git describe --abbrev=0 --tags > /dev/null 2>&1
if (( $? )) ; then
	build=$(git rev-list HEAD | wc -l | tr -d '\n' | tr -d ' ')
else
	build=$(git rev-list  `git rev-list --tags --no-walk --max-count=1`..HEAD --count)
fi
chash=$(git rev-parse --short HEAD | tr -d '\n' | tr -d ' ')

echo "/*******************************************************************************" > $filename
echo "" >> $filename
echo "                         Generated file : do not edit" >> $filename
echo "" >> $filename
echo "*******************************************************************************/" >> $filename
echo "" >> $filename
echo "#include \"Version.hh\"" >> $filename
echo "#include <string>" >> $filename
echo "" >> $filename
echo "using namespace std;" >> $filename
echo "" >> $filename

echo -n "const int RAYON_BUILD_VERSION = " >> $filename
echo -n $build >> $filename
echo ";" >> $filename
echo "" >> $filename

echo -n "const char* const RAYON_COMMIT_HASH = \"" >> $filename
echo -n $chash >> $filename
echo "\";" >> $filename
echo "" >> $filename

echo "const char* const RayOn::version()" >> $filename
echo "{" >> $filename
echo "  return \"$major.$minor.$build ($chash)\";" >> $filename
echo "}" >> $filename

exit 0

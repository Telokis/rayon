#!/bin/sh

hook="#!bin/sh\nsource ./scripts/generate_version.sh\nexit 0"
hooks_files="post-checkout post-merge post-commit"

for file in $hooks_files; do
	echo "$file"
    echo -e $hook > "../.git/hooks/$file"
done

cd ..
./scripts/generate_version.sh

exit 0

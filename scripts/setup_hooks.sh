#!/bin/bash

if [ "${PWD##*/}" != "scripts" ] ; then
    echo "Error, this script must run from the scripts folder."
    exit 1
fi

hook_version_handling="#!bin/sh\n./scripts/generate_version.sh"
hook_version_handling_files="post-checkout post-merge"

for file in $hook_version_handling_files; do
    echo -e $hook_version_handling >> "../.git/hooks/$file"
done

echo -e "#!bin/sh\n./scripts/handle_tags.sh\n./scripts/generate_version.sh" > "../.git/hooks/post-commit"

echo -e "#!bin/sh\n./scripts/setup_readme_version.sh" > "../.git/hooks/pre-commit"

cd ..
./scripts/generate_version.sh

exit 0

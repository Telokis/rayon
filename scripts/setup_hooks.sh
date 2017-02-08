#!/bin/sh

hook_version_handling="#!bin/sh\n./scripts/generate_version.sh"
hook_version_handling_files="post-checkout post-merge"

for file in $hook_version_handling_files; do
    echo -e $hook_version_handling >> "../.git/hooks/$file"
done

echo -e "#!bin/sh\n./scripts/handle_tags.sh\n./scripts/generate_version.sh" > "../.git/hooks/post-commit"

cd ..
./scripts/generate_version.sh

exit 0

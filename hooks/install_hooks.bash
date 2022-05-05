#!/usr/bin/env bash

SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." >/dev/null 2>&1 && pwd -P)"

cd $SRC_DIR

cp hooks/pre-commit .git/hooks/.
chmod +x .git/hooks/pre-commit

cp hooks/post-commit .git/hooks/.
chmod +x .git/hooks/post-commit

cp hooks/create_examples_implementation_tree.bash .git/hooks/.
chmod +x .git/hooks/create_examples_implementation_tree.bash

cp hooks/create_completes_from_diff.bash .git/hooks/.
chmod +x .git/hooks/create_completes_from_diff.bash

cp hooks/create_diffs.bash .git/hooks/.
chmod +x .git/hooks/create_diffs.bash

cp hooks/check_diffs.bash .git/hooks/.
chmod +x .git/hooks/check_diffs.bash

cp hooks/check_results.bash .git/hooks/.
chmod +x .git/hooks/check_results.bash

cp hooks/ensure_venv.bash .git/hooks/.
chmod +x .git/hooks/ensure_venv.bash

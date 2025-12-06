#!/usr/bin/env bash

# Determine the absolute path to this script's directory
TEST_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$TEST_DIR/.." && pwd)"

# Paths to bats-support and bats-assert (inside tests/)
SUPPORT_DIR="${TEST_DIR}/bats-support"
ASSERT_DIR="${TEST_DIR}/bats-assert"

# Verify that both dependencies exist
if [ ! -d "$SUPPORT_DIR" ] || [ ! -d "$ASSERT_DIR" ]; then
  echo "ERROR: Could not find bats-support or bats-assert directories in ${TEST_DIR}" >&2
  exit 1
fi

# Load libraries
load "${SUPPORT_DIR}/load.bash"
load "${ASSERT_DIR}/load.bash"

# Add build/ and project root to PATH for running compiled programs
PATH="${PROJECT_ROOT}/build:${PROJECT_ROOT}:$PATH"
export PATH

# Timeout for tests
export BATS_TEST_TIMEOUT=10
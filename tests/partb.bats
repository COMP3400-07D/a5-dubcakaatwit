#!/usr/bin/env bats

# -----------------------------------------
# Load shared test helpers
# -----------------------------------------
load "./test_helpers.bash"

# -----------------------------------------
# Tests for partb
# -----------------------------------------

@test "partb runs with no arguments" {
  run partb
  assert_success
}

@test "partb processes file1.txt" {
  run partb "${TEST_DIR}/file1.txt"
  assert_success

  # Compare to expected output
  expected="$(cat "${TEST_DIR}/partb_file1_output.txt")"
  assert_output "$expected"
}

@test "partb processes file2.txt" {
  run partb "${TEST_DIR}/file2.txt"
  assert_success

  expected="$(cat "${TEST_DIR}/partb_file2_output.txt")"
  assert_output "$expected"
}

@test "partb shows usage with -h" {
  run partb -h
  assert_success
  assert_output --partial "Usage"
}
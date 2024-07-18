#!/bin/bash

TEST_FOLDER="./bad"
PROGRAM="../cub3D"

# Check if the program exists
if [ ! -f "$PROGRAM" ]; then
  echo "Error: Program $PROGRAM not found!"
  exit 1
fi

for test_file in "$TEST_FOLDER"/*; do
  if [ -f "$test_file" ]; then
    echo "Running Valgrind on $test_file
"
    valgrind --leak-check=full "$PROGRAM" "$test_file"

    echo "
"
  else
    echo "No test files found in $TEST_FOLDER"
    exit 1
  fi
done

#!/bin/bash

echo "Script Name: $0"
echo "Number of arguments: $#"
echo "Arguments passed:"
for arg in "$@"; do
    echo "$arg"
done
echo "First argument: $1"
echo "Second argument: $2"
echo "Single string: $*"

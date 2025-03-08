#!/bin/sh
# Change into the build directory
cd build

if [ "$1" = "tests" ]; then
    echo "Running tests..."
    ./tests
elif [ "$1" = "main" ]; then
    echo "Running main executable..."
    ./main_exe
else
    echo "No valid argument provided. Defaulting to running main executable."
    ./tests
fi

# Keep the container alive (for inspection) after execution.
tail -f /dev/null
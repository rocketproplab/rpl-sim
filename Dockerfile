# Use an official Ubuntu base image
FROM ubuntu:22.04

# Install dependencies for building CMake and other required tools
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    libboost-program-options-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Install CMake 3.25+ by downloading and installing it manually
RUN wget https://github.com/Kitware/CMake/releases/download/v3.25.0/cmake-3.25.0-linux-x86_64.sh -O /tmp/cmake.sh && \
    chmod +x /tmp/cmake.sh && \
    /tmp/cmake.sh --prefix=/usr/local --skip-license && \
    rm /tmp/cmake.sh

# Verify the installed CMake version
RUN cmake --version

# Set the working directory in the container
WORKDIR /app

# Copy the project files to the container
COPY . .

# Create build directory
RUN mkdir -p build

# Set up CMake to build the project with verbose output
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_VERBOSE_MAKEFILE=ON

# Build the project
RUN cmake --build build

# Set the default command to run the main executable
# CMD ["build/main_exe"]

# Run in SSH Mode
CMD ["sh", "-c", "cd build && ./tests"]
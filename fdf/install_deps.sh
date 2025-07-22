#!/bin/bash

# Install dependencies for MLX42 on Linux
echo "Installing dependencies for MLX42..."

# Update package list
sudo apt-get update

# Install required packages
sudo apt-get install -y \
    build-essential \
    libx11-dev \
    libglfw3 \
    libglfw3-dev \
    libfreetype6-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxi-dev \
    libxcursor-dev \
    cmake \
    git

echo "Dependencies installed successfully!"
echo "You can now run 'make' to compile the project."

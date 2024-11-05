FROM ubuntu:22.04

# Add universe repository and install required packages
RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository universe && \
    apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libwayland-dev \
    wayland-protocols \
    libweston-9-dev \
    weston

# Create a working directory
WORKDIR /app

# Copy your source files
COPY simple-wayland-client.c .
COPY CMakeLists.txt . 
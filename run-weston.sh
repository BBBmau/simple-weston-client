#!/bin/bash

# Set up runtime directory if it doesn't exist
export XDG_RUNTIME_DIR=/run/user/$(id -u)
if [ ! -d "$XDG_RUNTIME_DIR" ]; then
    export XDG_RUNTIME_DIR=/tmp/$(id -u)-runtime-dir
    mkdir -p "$XDG_RUNTIME_DIR"
    chmod 0700 "$XDG_RUNTIME_DIR"
fi

# Basic Wayland environment setup
export XDG_SESSION_TYPE=wayland
export WAYLAND_DEBUG=1
export WESTON_DEBUG=1

# Make sure we have a display set
if [ -z "$DISPLAY" ]; then
    export DISPLAY=:0
fi

if ! command -v weston &> /dev/null; then
    echo "Weston is not installed. Installing now..."
    sudo apt-get update && sudo apt-get install -y weston
fi

# Start Weston in nested mode using X11 backend
weston --backend=x11-backend.so --width=1024 --height=768 &


# Wait for Weston to start
sleep 2

# Print some debugging information
echo "Checking if Weston is running..."
ps aux | grep weston
echo "Checking for Wayland socket..."
ls -l $XDG_RUNTIME_DIR/wayland-* || echo "No Wayland socket found"

# Run your client
./build/simple-wayland-client
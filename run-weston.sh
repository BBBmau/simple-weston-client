#!/bin/bash
export XDG_RUNTIME_DIR=/tmp
mkdir -p "$XDG_RUNTIME_DIR"
chmod 0700 "$XDG_RUNTIME_DIR"
weston --backend=headless-backend.so &
sleep 2  # Give Weston time to start
./build/simple-wayland-client 
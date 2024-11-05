# simple-wayland-client
this repo is to play around with weston in order to create a compatibilty layer between xg_shell &lt;-> wl_shell

### IMPORTANT

- This repo is only tested on linux, specifically ubuntu 24.04
- attempts were made to get it working on macos and docker containres but it was not successful.
- found it much easier to run on native ubuntu 24.04
- you are able to simple run the application with `./run-weston.sh` and not use docker. You should see the following output:
![alt text](<Screenshot from 2024-11-04 22-10-04.png>)

## Build Instructions

```
docker build -t simple-wayland-client .
```

## Run Instructions

```
docker run -it --rm \
    -v "$(pwd):/app" \
    -v "$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY" \
    -v "/dev/dri:/dev/dri" \
    -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
    -e WAYLAND_DISPLAY=$WAYLAND_DISPLAY \
    simple-wayland-client /bin/bash
```

```
# Inside the container, build and run the application:
mkdir build
cd build
cmake ..
make
cd ..
./run-weston.sh
```

You should see the followiong output:

```
root@60e8196a12ba:/app/build# make
[ 50%] Building C object CMakeFiles/simple-wayland-client.dir/simple-wayland-client.c.o
[100%] Linking C executable simple-wayland-client
[100%] Built target simple-wayland-client
root@60e8196a12ba:/app/build# cd ..
root@60e8196a12ba:/app# ./run-weston.sh 
Date: 2024-11-02 UTC
[04:11:33.322] weston 9.0.0
               https://wayland.freedesktop.org
               Bug reports to: https://gitlab.freedesktop.org/wayland/weston/issues/
               Build: 9.0.0
[04:11:33.322] Command line: weston --backend=headless-backend.so
[04:11:33.322] OS: Linux, 6.6.26-linuxkit, #1 SMP Sat Apr 27 04:13:19 UTC 2024, aarch64
[04:11:33.322] Starting with no config file.
[04:11:33.323] Output repaint window is 7 ms maximum.
[04:11:33.323] Loading module '/usr/lib/aarch64-linux-gnu/libweston-9/headless-backend.so'
[04:11:33.323] Registered plugin API 'weston_windowed_output_api_v1' of size 16
[04:11:33.323] Output 'headless' enabled with head(s) headless
[04:11:33.323] Compositor capabilities:
               arbitrary surface rotation: no
               screen capture uses y-flip: no
               presentation clock: CLOCK_MONOTONIC_RAW, id 4
               presentation clock resolution: 0.001000000 s
[04:11:33.323] libwayland: unable to lock lockfile /tmp/wayland-0.lock, maybe another compositor is running
[04:11:33.323] libwayland: unable to lock lockfile /tmp/wayland-1.lock, maybe another compositor is running
[04:11:33.323] Loading module '/usr/lib/aarch64-linux-gnu/weston/desktop-shell.so'
[04:11:33.323] launching '/usr/lib/aarch64-linux-gnu/weston-keyboard'
[04:11:33.324] launching '/usr/lib/aarch64-linux-gnu/weston-desktop-shell'
could not load cursor 'dnd-move'
could not load cursor 'dnd-move'
could not load cursor 'dnd-copy'
could not load cursor 'dnd-copy'
could not load cursor 'dnd-none'
could not load cursor 'dnd-none'
Successfully connected to Wayland display!
```
#include <stdio.h>
#include <wayland-client.h>

struct wl_display *display = NULL;

int main(int argc, char *argv[]) {
    // Connect to the default Wayland display
    display = wl_display_connect(NULL);
    if (display == NULL) {
        fprintf(stderr, "Failed to connect to Wayland display.\n");
        return 1;
    }

    printf("Successfully connected to Wayland display!\n");

    // Cleanup
    wl_display_disconnect(display);
    return 0;
}
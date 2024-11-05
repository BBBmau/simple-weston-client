#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>
#include <wayland-client-protocol.h>

struct client_state {
    struct wl_display *display;
    struct wl_registry *registry;
    struct wl_compositor *compositor;
    struct wl_surface *surface;
    struct wl_shell *shell;
    struct wl_shell_surface *shell_surface;
};

static void registry_global(void *data, struct wl_registry *registry,
                          uint32_t name, const char *interface, uint32_t version) {
    struct client_state *state = data;

    if (strcmp(interface, "wl_compositor") == 0) {
        state->compositor = wl_registry_bind(registry, name,
                                          &wl_compositor_interface, 1);
    } else if (strcmp(interface, "wl_shell") == 0) {
        state->shell = wl_registry_bind(registry, name,
                                     &wl_shell_interface, 1);
    }
}

static void registry_global_remove(void *data,
                                struct wl_registry *registry, uint32_t name) {
    // Handle removal of global objects
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove,
};

int main(int argc, char *argv[]) {
    struct client_state state = { 0 };

    // Connect to display
    state.display = wl_display_connect(NULL);
    if (!state.display) {
        fprintf(stderr, "Failed to connect to Wayland display\n");
        return 1;
    }

    // Get registry
    state.registry = wl_display_get_registry(state.display);
    wl_registry_add_listener(state.registry, &registry_listener, &state);
    wl_display_roundtrip(state.display);

    // Create surface
    state.surface = wl_compositor_create_surface(state.compositor);
    if (!state.surface) {
        fprintf(stderr, "Can't create surface\n");
        return 1;
    }

    // Create shell surface
    state.shell_surface = wl_shell_get_shell_surface(state.shell, state.surface);
    if (!state.shell_surface) {
        fprintf(stderr, "Can't create shell surface\n");
        return 1;
    }

    wl_shell_surface_set_toplevel(state.shell_surface);

    printf("Window created! Press Ctrl+C to exit\n");

    // Main event loop
    while (wl_display_dispatch(state.display) != -1) {
        // Handle events
    }

    // Cleanup
    if (state.shell_surface)
        wl_shell_surface_destroy(state.shell_surface);
    if (state.surface)
        wl_surface_destroy(state.surface);
    if (state.shell)
        wl_shell_destroy(state.shell);
    if (state.compositor)
        wl_compositor_destroy(state.compositor);
    if (state.registry)
        wl_registry_destroy(state.registry);
    if (state.display)
        wl_display_disconnect(state.display);

    return 0;
}
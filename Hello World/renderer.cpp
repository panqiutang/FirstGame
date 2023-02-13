/* Fill all pixels with a color */
void clear_screen(unsigned int color) {
    u32* pixel = (u32*)render_state.memory;
    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = color;
        }
    }
}

/* Draw a rectangle with x coordinates between [x0, x1] and y coordinates between [y0, y1] in pixels */
void draw_rectangle_pixels(int x0, int y0, int x1, int y1, u32 color) {
    x0 = clamp(0, x0, render_state.width);
    x1 = clamp(0, x1, render_state.width);
    y0 = clamp(0, y0, render_state.height);
    y1 = clamp(0, y1, render_state.height);

    for (int y = y0; y < y1; y++) {
        u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
        for (int x = x0; x < x1; x++) {
            *pixel++ = color;
        }
    }
}

/* Scale down coordinate percentages */
global_variable float render_scale = 0.01f;

/*
* Draw rectangle centered at [x, y] with width, height, and color
* x, y: percentages between [-50, 50], or [-0.5, 0.5] after applying scale down
* width, height: pixels
*/
void draw_rectangle(float x, float y, int width, int height, u32 color) {
    // calculate borders
    int x0 = x * render_state.width * render_scale - width / 2.0f;
    int x1 = x * render_state.width * render_scale + width / 2.0f;
    int y0 = y * render_state.height * render_scale - height / 2.0f;
    int y1 = y * render_state.height * render_scale + height / 2.0f;

    // position rectangle at center of height (can also choose width)
    x0 += render_state.height / 2.0f;
    x1 += render_state.height / 2.0f;
    y0 += render_state.height / 2.0f;
    y1 += render_state.height / 2.0f;

    draw_rectangle_pixels(x0, y0, x1, y1, color);
}
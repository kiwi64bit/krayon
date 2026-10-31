#define KRAYON_IMPLEMENTATION
#include "krayon.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "dev_deps/stb_image_write.h"
#include <stdlib.h>
#include <time.h>

uint32_t random_color()
{
    uint32_t r = (uint32_t)(rand() % 256u);
    uint32_t g = (uint32_t)(rand() % 256u);
    uint32_t b = (uint32_t)(rand() % 256u);

    return KRAYON_COLOR_RGBA(r, g, b, 255u);
}

#define WIDTH  400
#define HEIGHT 400

uint8_t data[WIDTH * HEIGHT * 4];
KrayonCanvas canvas = {
    .width = WIDTH,
    .height = HEIGHT,
    .data = data,
};

int main()
{
    // srand(time(NULL));
    krayon_fill_canvas(canvas, KRAYON_COLOR_BLACK);

    int rows = 5, cols = 5;

    int cell_width = WIDTH / cols;
    int cell_height = HEIGHT / rows;

    int offset_x, offset_y;
    int x1, y1, x2, y2, x3, y3;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            offset_x = x * cell_width;
            offset_y = y * cell_height;

            x1 = rand() % 100;
            y1 = rand() % 100;
            x2 = rand() % 100;
            y2 = rand() % 100;
            x3 = rand() % 100;
            y3 = rand() % 100;

            krayon_fill_triangle(
                canvas,
                offset_x + x1 * cell_width / 100,
                offset_y + y1 * cell_height / 100,
                offset_x + x2 * cell_width / 100,
                offset_y + y2 * cell_height / 100,
                offset_x + x3 * cell_width / 100,
                offset_y + y3 * cell_height / 100,
                random_color()
            );
        }
    }

    stbi_write_png(
        "examples/images/fill_triangle.png",
        canvas.width,
        canvas.height,
        4,
        canvas.data,
        canvas.width * 4
    );
    return 0;
}
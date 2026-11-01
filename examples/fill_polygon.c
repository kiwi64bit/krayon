#define KRAYON_IMPLEMENTATION
#include "krayon.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "dev_deps/stb_image_write.h"

uint32_t random_color()
{
    uint32_t r = (uint32_t)(rand() % 256u);
    uint32_t g = (uint32_t)(rand() % 256u);
    uint32_t b = (uint32_t)(rand() % 256u);

    return KRAYON_COLOR_RGBA(r, g, b, 255u);
}

int *scale_polygon(int *polygon, size_t count, double scale_x, double scale_y)
{
    for (size_t i = 0; i < count * 2; i += 2) {
        polygon[i] *= scale_x;
        polygon[i + 1] *= scale_y;
    }

    return polygon;
}

int *local_to_screen(int *polygon, size_t count, int pos_x, int pos_y)
{
    for (size_t i = 0; i < count * 2; i += 2) {
        polygon[i] += pos_x;
        polygon[i + 1] += pos_y;
    }

    return polygon;
}

#define WIDTH  400
#define HEIGHT 400

uint8_t data[WIDTH * HEIGHT * 4];
KrayonCanvas canvas = {
    .width = WIDTH,
    .height = HEIGHT,
    .data = data,
};

// Triangle
int polygon1[] = {50, 10, 15, 70, 85, 70};
const size_t polygon1_count = 3;

// Parallelogram
int polygon2[] = {30, 20, 90, 20, 70, 80, 10, 80};
const size_t polygon2_count = 4;

// Diamond
int polygon3[] = {50, 10, 60, 50, 50, 90, 40, 50};
const size_t polygon3_count = 4;

// Pentagon
int polygon4[] = {50, 10, 12, 38, 26, 82, 74, 82, 88, 38};
const size_t polygon4_count = 5;

// Trapezoid
int polygon5[] = {30, 15, 70, 15, 90, 85, 10, 85};
const size_t polygon5_count = 4;

// Hexagon
int polygon6[] = {90, 50, 70, 15, 30, 15, 10, 50, 30, 85, 70, 85};
const size_t polygon6_count = 6;

// Square 45deg
int polygon7[] = {50, 10, 90, 50, 50, 90, 10, 50};
const size_t polygon7_count = 4;

// Jewel
int polygon8[] = {50, 10, 70, 25, 70, 75, 50, 90, 30, 75, 30, 25};
const size_t polygon8_count = 6;

// Tilted Diamond
int polygon9[] = {15, 15, 68, 32, 85, 85, 32, 68};
const size_t polygon9_count = 4;

int *polygons[] = {
    polygon1,
    polygon2,
    polygon3,
    polygon4,
    polygon5,
    polygon6,
    polygon7,
    polygon8,
    polygon9,
};

size_t polygon_counts[] = {
    polygon1_count,
    polygon2_count,
    polygon3_count,
    polygon4_count,
    polygon5_count,
    polygon6_count,
    polygon7_count,
    polygon8_count,
    polygon9_count,
};

int main()
{
    krayon_fill_canvas(canvas, KRAYON_COLOR_BLACK);

    int rows = 3, cols = 3;

    int cell_width = WIDTH / cols;
    int cell_height = HEIGHT / rows;

    int offset_x, offset_y;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            offset_x = x * cell_width;
            offset_y = y * cell_height;

            int *polygon = polygons[y * cols + x];
            size_t count = polygon_counts[y * cols + x];

            scale_polygon(
                polygon,
                count,
                cell_width / 100.0,
                cell_height / 100.0
            );
            local_to_screen(polygon, count, offset_x, offset_y);

            krayon_fill_polygon(canvas, polygon, count, random_color());
        }
    }

    stbi_write_png(
        "examples/images/fill_polygon.png",
        canvas.width,
        canvas.height,
        4,
        canvas.data,
        canvas.width * 4
    );
    return 0;
}
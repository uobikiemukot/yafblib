/* See LICENSE for licence details. */
#include "fb/common.h"

void draw_point(struct framebuffer_t *fb, int height, int width, uint32_t color)
{
	uint32_t pixel;

	/* color2pixel convert from 24/32bit color (see color.h)
		to framebuffer dependent pixel format */
	pixel = color2pixel(&fb->info, color);

	memcpy(fb->fp + height * fb->info.line_length
		+ width * fb->info.bytes_per_pixel, &pixel, fb->info.bytes_per_pixel);
}

int main()
{
	struct framebuffer_t fb;

	/* initialize framebuffer at first */
	if (fb_init(&fb) == false)
		return EXIT_FAILURE;

	/* draw something */
	for (int h = 0; h < fb.info.height; h++) {
		for (int w = 0; w < fb.info.width; w++) {
			draw_point(&fb, h, w, h * fb.info.width + w);
		}
	}

	/* release framebuffer */
	fb_die(&fb);
	return EXIT_SUCCESS;
}

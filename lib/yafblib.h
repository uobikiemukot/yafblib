/* See LICENSE for licence details. */

#include <stdint.h>
#include <stdbool.h>

#ifndef YAFBLIB_H
#define YAFBLIB_H

/* common framebuffer struct/enum */
enum fb_type {
	YAFT_FB_TYPE_PACKED_PIXELS = 0,
	YAFT_FB_TYPE_PLANES,
	YAFT_FB_TYPE_UNKNOWN,
};

enum fb_visual {
	YAFT_FB_VISUAL_TRUECOLOR = 0,
	YAFT_FB_VISUAL_DIRECTCOLOR,
	YAFT_FB_VISUAL_PSEUDOCOLOR,
	YAFT_FB_VISUAL_UNKNOWN,
};

struct fb_info_t {
	struct bitfield_t {
		int length;
		int offset;
	} red, green, blue;
	int width, height;      /* display resolution */
	long screen_size;       /* screen data size (byte) */
	int line_length;        /* line length (byte) */
	int bits_per_pixel;
	int bytes_per_pixel;
	enum fb_type type;
	enum fb_visual visual;
	int reserved[4];        /* os specific data */
};

struct framebuffer_t {
	int fd;                   /* file descriptor of framebuffer */
	unsigned char *fp;        /* pointer of framebuffer */
	struct fb_info_t info;
	//cmap_t *cmap, *cmap_orig; /* os specific cmap */
};

/* common framebuffer functions */
//int cmap_update(int fd, cmap_t *cmap);
uint32_t color2pixel(struct fb_info_t *info, uint32_t color);
bool fb_init(struct framebuffer_t *fb);
void fb_die(struct framebuffer_t *fb);

#endif /* YAFBLIB_H */

/* See LICENSE for licence details. */
#if defined(__linux__)

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "util.h"
#include "linux.h"

cmap_t *cmap, *cmap_orig;

const char *fb_path = "/dev/fb0";

const unsigned int bit_mask[] = {
	0x00000000,
	0x00000001, 0x00000003, 0x00000007, 0x0000000F,
	0x0000001F, 0x0000003F, 0x0000007F, 0x000000FF,
	0x000001FF, 0x000003FF, 0x000007FF, 0x00000FFF,
	0x00001FFF, 0x00003FFF, 0x00007FFF, 0x0000FFFF,
	0x0001FFFF, 0x0003FFFF, 0x0007FFFF, 0x000FFFFF,
	0x001FFFFF, 0x003FFFFF, 0x007FFFFF, 0x00FFFFFF,
	0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF, 0x0FFFFFFF,
	0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF,
};

/* os specific ioctl */
void alloc_cmap(cmap_t *cmap, int colors)
{
	cmap->start  = 0;
	cmap->len    = colors;
	cmap->red    = (__u16 *) ecalloc(colors, sizeof(__u16));
	cmap->green  = (__u16 *) ecalloc(colors, sizeof(__u16));
	cmap->blue   = (__u16 *) ecalloc(colors, sizeof(__u16));
	cmap->transp = NULL;
}

int put_cmap(int fd, cmap_t *cmap)
{
	return ioctl(fd, FBIOPUTCMAP, cmap);
}

int get_cmap(int fd, cmap_t *cmap)
{
	return ioctl(fd, FBIOGETCMAP, cmap);
}

/* initialize struct fb_info_t */
void set_bitfield(struct fb_var_screeninfo *vinfo,
	struct bitfield_t *red, struct bitfield_t *green, struct bitfield_t *blue)
{
	red->length   = vinfo->red.length;
	green->length = vinfo->green.length;
	blue->length  = vinfo->blue.length;

	red->offset   = vinfo->red.offset;
	green->offset = vinfo->green.offset;
	blue->offset  = vinfo->blue.offset;
}

enum fb_type set_type(__u32 type)
{
	if (type == FB_TYPE_PACKED_PIXELS)
		return YAFT_FB_TYPE_PACKED_PIXELS;
	else if (type == FB_TYPE_PLANES)
		return YAFT_FB_TYPE_PLANES;
	else
		return YAFT_FB_TYPE_UNKNOWN;
}

enum fb_visual set_visual(__u32 visual)
{
	if (visual == FB_VISUAL_TRUECOLOR)
		return YAFT_FB_VISUAL_TRUECOLOR;
	else if (visual == FB_VISUAL_DIRECTCOLOR)
		return YAFT_FB_VISUAL_DIRECTCOLOR;
	else if (visual == FB_VISUAL_PSEUDOCOLOR)
		return YAFT_FB_VISUAL_PSEUDOCOLOR;
	else
		return YAFT_FB_VISUAL_UNKNOWN;
}

bool set_fbinfo(int fd, struct fb_info_t *info)
{
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;

	if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo)) {
		logging(ERROR, "ioctl: FBIOGET_FSCREENINFO failed\n");
		return false;
	}

	if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)) {
		logging(ERROR, "ioctl: FBIOGET_VSCREENINFO failed\n");
		return false;
	}

	set_bitfield(&vinfo, &info->red, &info->green, &info->blue);

	info->width  = vinfo.xres;
	info->height = vinfo.yres;
	info->screen_size = finfo.smem_len;
	info->line_length = finfo.line_length;

	info->bits_per_pixel  = vinfo.bits_per_pixel;
	info->bytes_per_pixel = my_ceil(info->bits_per_pixel, BITS_PER_BYTE);

	info->type   = set_type(finfo.type);
	info->visual = set_visual(finfo.visual);

	/* check screen [xy]offset and initialize because linux console changes these values */
	if (vinfo.xoffset != 0 || vinfo.yoffset != 0) {
		vinfo.xoffset = vinfo.yoffset = 0;
		if (ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo))
			logging(WARN, "couldn't reset offset (x:%d y:%d)\n", vinfo.xoffset, vinfo.yoffset);
	}

	return true;
}

#endif /* defined(__linux__) */

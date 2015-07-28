/* See LICENSE for licence details. */
#if defined(__OpenBSD__)

#include <sys/param.h>
#include <dev/wscons/wsdisplay_usl_io.h>
#include <dev/wscons/wsconsio.h>
#include <dev/wscons/wsksymdef.h>

typedef struct wsdisplay_cmap cmap_t;

extern cmap_t *cmap, *cmap_orig;
extern const char *fb_path;
extern const unsigned int bit_mask[];

enum opensd_misc {
	BITS_PER_RGB  = 8,
	BITS_PER_BYTE = 8,
	CMAP_COLOR_LENGTH = sizeof(u_char) * BITS_PER_BYTE,
	FB_WIDTH  = 640,
	FB_HEIGHT = 480,
	FB_DEPTH  = 8,
};

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

#endif /* defined(__OpenBSD__) */

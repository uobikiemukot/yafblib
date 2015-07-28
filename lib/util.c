/* See LICENSE for licence details. */
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

/* error functions */
void logging(enum loglevel loglevel, char *format, ...)
{
	va_list arg;
	const char *loglevel2str[] = {
		[DEBUG] = "DEBUG",
		[WARN]  = "WARN",
		[ERROR] = "ERROR",
		[FATAL] = "FATAL",
	};

	/* debug message is available on verbose mode */
	if ((loglevel == DEBUG) && (VERBOSE == false))
		return;

	fprintf(stderr, ">>%s<<\t", loglevel2str[loglevel]);

	va_start(arg, format);
	vfprintf(stderr, format, arg);
	va_end(arg);
}

/* wrapper of C functions */
int eopen(const char *path, int flag)
{
	int fd;
	errno = 0;

	if ((fd = open(path, flag)) < 0) {
		logging(ERROR, "couldn't open \"%s\"\n", path);
		logging(ERROR, "open: %s\n", strerror(errno));
	}
	return fd;
}

int eclose(int fd)
{
	int ret;
	errno = 0;

	if ((ret = close(fd)) < 0)
		logging(ERROR, "close: %s\n", strerror(errno));

	return ret;
}

FILE *efopen(const char *path, char *mode)
{
	FILE *fp;
	errno = 0;

	if ((fp = fopen(path, mode)) == NULL) {
		logging(ERROR, "couldn't open \"%s\"\n", path);
		logging(ERROR, "fopen: %s\n", strerror(errno));
	}
	return fp;
}

int efclose(FILE *fp)
{
	int ret;
	errno = 0;

	if ((ret = fclose(fp)) < 0)
		logging(ERROR, "fclose: %s\n", strerror(errno));

	return ret;
}

void *emmap(void *addr, size_t len, int prot, int flag, int fd, off_t offset)
{
	void *fp;
	errno = 0;

	if ((fp = mmap(addr, len, prot, flag, fd, offset)) == MAP_FAILED)
		logging(ERROR, "mmap: %s\n", strerror(errno));

	return fp;
}

int emunmap(void *ptr, size_t len)
{
	int ret;
	errno = 0;

	if ((ret = munmap(ptr, len)) < 0)
		logging(ERROR, "munmap: %s\n", strerror(errno));

	return ret;
}

void *ecalloc(size_t nmemb, size_t size)
{
	void *ptr;
	errno = 0;

	if ((ptr = calloc(nmemb, size)) == NULL)
		logging(ERROR, "calloc: %s\n", strerror(errno));

	return ptr;
}

/* other functions */
int my_ceil(int val, int div)
{
	if (div == 0)
		return 0;
	else
		return (val + div - 1) / div;
}

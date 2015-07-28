/* See LICENSE for licence details. */
/* error functions */
enum debug {
	VERBOSE = false,
};

enum loglevel {
	DEBUG = 0,
	WARN,
	ERROR,
	FATAL,
};

void logging(enum loglevel loglevel, char *format, ...);

/* wrapper of C functions */
int eopen(const char *path, int flag);
int eclose(int fd);
FILE *efopen(const char *path, char *mode);
int efclose(FILE *fp);
void *emmap(void *addr, size_t len, int prot, int flag, int fd, off_t offset);
int emunmap(void *ptr, size_t len);
void *ecalloc(size_t nmemb, size_t size);

/* other functions */
int my_ceil(int val, int div);

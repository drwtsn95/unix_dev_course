#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

int remove(char *name) {
	int (*old_remove)(char *) = dlsym(RTLD_NEXT, "remove");

	if (strstr(name, "PROTECT") != NULL) {
		return -1;
	}
	return old_remove(name);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <rhash.h>
#include <errno.h>
#include "config.h"

#if USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

size_t getreadline(char **line) {
#ifdef USE_READLINE
	if (*line) {
		free(*line);
	}
	*line = readline(NULL);
	if (*line == NULL) {
		return -1;
	}
	return strlen(*line);
#else
	size_t len = 0;
	return getline(line, &len, stdin);
#endif
}

int gethash(const char *input, char *output, int hashtype, int encoding) {
	char hash[64];
	int res;
	
	if (input[0] == '"') {
		//skip first char
		res = rhash_msg(hashtype, input + 1, strlen(input) - 1, hash);
	} else {
		res = rhash_file(hashtype, input, hash);
	}

	if (res < 0) {
		fprintf(stderr, "Hash calculation failed\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	rhash_print_bytes(output, hash, rhash_get_digest_size(hashtype), encoding);
	return 0;
}

int main(int argc, char **argv) {
	rhash_library_init();
	char output[256];
	char *line = NULL;

	while (getreadline(&line) != -1) { //obviosly if smth read without error it ll have positive length

		char *command = strtok(line, " ");

		int encoding = isupper(command[0]) ? RHPR_HEX : RHPR_BASE64;
		int hashtype;

		if (!strcasecmp(command, "md5")) {
			hashtype = RHASH_MD5;
		} else if (!strcasecmp(command, "sha1")) {
			hashtype = RHASH_SHA1;
		} else if (!strcasecmp(command, "tth")) {
			hashtype = RHASH_TTH;
		} else {
			fprintf(stderr, "Wrong command\n");
			continue;
		}

		char *input = strtok(NULL, " ");
		input = strtok(input, "\n");

		if (input == NULL || *input == '\0') {
			fprintf(stderr, "Empty input\n");
			continue;
		}

		if (gethash(input, output, hashtype, encoding) == 0) {
			fprintf(stdout, "%s\n", output);
		}

	}

	if (line) {
		free(line);
	}
	return 0;
}

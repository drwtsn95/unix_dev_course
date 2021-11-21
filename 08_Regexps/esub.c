#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>

#include "config.h"

#define NMATCH 100
#define ERROR_MSG_SIZE 128

int check_sub(regmatch_t *pmatch, const char *sub) {
	int maybe_pocket = 0;
	const char *ptr;
	for (ptr = sub; *ptr; ptr++) {

		if (*ptr == '\\') { //backslash encountered
			maybe_pocket = !maybe_pocket; // + helps_us to cut odd backslashes
		} else if (maybe_pocket) {	

			if (!isdigit(*ptr)) {
				fprintf(stderr, "Bad escaped character '%c' in substitution string in position %ld\n", *ptr, ptr - sub + 1);
				return -1;
			} 
			//else we resolving pocket number now
			int p_num = *ptr - '0';
			if (pmatch[p_num].rm_so < 0) {
				fprintf(stderr, "Nonexistent pocket number %d\n", p_num);
				return -1;
			}
			maybe_pocket = 0;
		}
	}
	//what aba last backslash
	if (maybe_pocket) {
		fprintf(stderr, "Bad escaped character (unresolved)\n");
		return -1;
	}

	return 0;
}

void substitute(const char *source, const char *sub, regmatch_t *pmatch) {
	int maybe_pocket = 0;
	const char *ptr;
	//everything is pre-checked now, let's just print
	printf("%.*s", pmatch[0].rm_so, source); //before first match

	for (ptr = sub; *ptr; ptr++) {
		if (*ptr == '\\') { //backslash encountered
			if (maybe_pocket) {
				putchar(*ptr); //just print escaped backslash
			}
			maybe_pocket = !maybe_pocket;
		} else if (maybe_pocket) {
			int p_num = *ptr - '0';
			int start = (int) pmatch[p_num].rm_so;
			int end = (int) pmatch[p_num].rm_eo;

			printf("%.*s", end - start, source + start);
			maybe_pocket = 0;
		} else {
			putchar(*ptr);
		}
	}
	printf("%s\n", source + pmatch[0].rm_eo);
}


int main(int argc, char **argv) {

	char error_msg[ERROR_MSG_SIZE];

	if (argc != 4) {
		fprintf(stderr, "Usage: ./esub regexp substitution string\n");
		return -1;
	}

	const char *regex_str = argv[1];
	const char *sub = argv[2];
	const char *source = argv[3];

	regex_t regex;
	regmatch_t  pmatch[NMATCH];

	int status_code = regcomp(&regex, regex_str, REG_EXTENDED);

	if (status_code != 0) {
		regerror(status_code, &regex, error_msg, ERROR_MSG_SIZE);
		fprintf(stderr, "Compilation failed: %s\n", error_msg);
		regfree(&regex);
		return -1;
	}

	status_code = regexec(&regex, source, NMATCH, pmatch, 0);

	if (status_code != 0) {
		if (status_code == REG_NOMATCH) {
			printf("%s\n", source);
			return 0;
		} else {
			regerror(status_code, &regex, error_msg, ERROR_MSG_SIZE);
			fprintf(stderr, "Matching failed: %s\n", error_msg);
			regfree(&regex);
			return -1;
		}
	}

	status_code = check_sub(pmatch, sub);

	if (status_code != 0) {
		return status_code;
	}

	substitute(source, sub, pmatch);

	return 0;
}
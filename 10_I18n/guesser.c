#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <libintl.h>
#include "config.h"

#define LOCALE_PATH getenv("PWD")
#define _(STRING) gettext(STRING)

int main() {
	setlocale (LC_ALL, "");
	bindtextdomain ("guesser", LOCALE_PATH);
	textdomain ("guesser");

	int left = 0, right = 100, center;
	char answer_buf[13];

	printf(_("Make a number from 1 to 100\n"));

	while (left < right) {
		center = (left + right) / 2;

		printf(_("Is your number greater than %d? (yes/no)\n"), center);

		fgets(answer_buf, sizeof(answer_buf), stdin);

		if (!strcasecmp(answer_buf, _("yes\n"))) {
			left = center + 1;
		} else if (!strcasecmp(answer_buf, _("no\n"))) {
			right = center;
		}
	}
	printf(_("Your number is %d\n"), left);
	return 0;
}

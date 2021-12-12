/**
 * @file guesser.c
 * @author drwtsn
 * @brief Number guesser
 * @version 1.0.0
 * @date 2021-12-12
 * 
 * Usage: guesser [OPTIONS]
 * - -\-help -- print this help
 * - -\-version -- print version
 * - -r -- Roman mode
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <libintl.h>
#include "config.h"

#define LOCALE_PATH getenv("PWD")
#define _(STRING) gettext(STRING)
#define HELP _("Number guesser tries to guess your number from 1 to 100\n\
\n\
Usage: guesser [OPTIONS] \n\
\n\
	--help					print this help\n\
	--version				print version number\n\
	-r					print numbers in Roman numeral system\n\
\n\
")

static char *romans_table[] = {"N", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII",
                         "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV",
                         "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI",
                         "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII",
                         "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII",
                         "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI",
                         "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII",
                         "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

/**
* Converts numbers from the Arabic decimal numeral system to the Roman numeral system
* @param a The number from 1 to 100
* 
* @returns The number in the Roman numeral system
*/
char *dec_to_roman(int num) {
	return romans_table[num];
}

/**
* Converts numbers from the Roman numeral system to the Arabic decimal numeral system
* @param a The number from I to C
* 
* @returns The number in the Arabic numeral system or -1
*/
int fromRomans(char *num) {
	for (int i = 0; i < sizeof(romans_table); i++) {
		if (!strcasecmp(num, romans_table[i])) {
			return i;
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	setlocale (LC_ALL, "");
	bindtextdomain ("guesser", LOCALE_PATH);
	textdomain ("guesser");

	int left = 0, right = 100, center;
	char answer_buf[13];
	int roman_mode = 0;

	if (argc > 1) {
		if (!strcmp(argv[1], "--help")) {
			printf(HELP);
			return 0;
		} else if (!strcmp(argv[1], "--version")) {
			printf(VERSION);
			return 0;
		} else if (!strcmp(argv[1], "-r")) {
			roman_mode = 1;
		}
	}

	if (roman_mode) {
		printf(_("Make a number from %s to %s\n"), dec_to_roman(1), dec_to_roman(100));
	} else {
		printf(_("Make a number from 1 to 100\n"));
	}

	while (left < right) {
		center = (left + right) / 2;
		if (roman_mode) {
			printf(_("Is your number greater than %s? (yes/no)\n"), dec_to_roman(center));
		} else {
			printf(_("Is your number greater than %d? (yes/no)\n"), center);
		}

		fgets(answer_buf, sizeof(answer_buf), stdin);

		if (!strcasecmp(answer_buf, _("yes\n"))) {
			left = center + 1;
		} else if (!strcasecmp(answer_buf, _("no\n"))) {
			right = center;
		}
	}
	if (roman_mode) {
		printf(_("Your number is %s\n"), dec_to_roman(left));
	} else {
		printf(_("Your number is %d\n"), left);		
	}
	return 0;
}

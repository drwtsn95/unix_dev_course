bin_PROGRAMS=guesser
AM_CFLAGS = -D LOCALEDIR='"$(localedir)"'

pkgdata_DATA=ru/LC_MESSAGES/guesser.mo

pkgdatadir=$(localedir)/ru/LC_MESSAGES


man1_MANS = guesser.1

%.1:	%
	help2man --no-info --output=$@ --name='@PACKAGE_NAME@' ./$<

ru/LC_MESSAGES/guesser.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po: messages.pot
	msgmerge -U $@ $<

messages.pot: guesser.pot guesser.c
	xgettext -k_ -c guesser.c -o messages.new.pot
	cp guesser.pot messages.pot
	msgmerge -U messages.pot messages.new.pot

clean:
	rm -rf messages*.pot guesser guesser.o *.po~ ru

gitclean: maintainer-clean
	git clean -fd

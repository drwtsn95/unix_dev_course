bin_PROGRAMS=guesser
pkgdata_DATA=ru/LC_MESSAGES/guesser.mo guesser.1
HELP2MAN = help2man

@DX_RULES@

all-local: doxygen-doc

ru/LC_MESSAGES/guesser.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po: messages.pot
	msgmerge -U $@ $<

messages.pot: guesser.pot guesser.c
	xgettext -k_ -c guesser.c -o messages.new.pot
	cp guesser.pot messages.pot
	msgmerge -U messages.pot messages.new.pot

%.1: %
	-$(HELP2MAN) --no-info --output=$@ --name='@PACKAGE_NAME@' ./guesser

clean:
	rm -rf messages*.pot guesser guesser.o *.po~ ru

gitclean: maintainer-clean
	git clean -fd


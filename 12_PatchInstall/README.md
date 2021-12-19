# Build

`autoreconf -fisv && ./configure --prefix=/usr && make`  

`make install DESTDIR=<directory_name>`

# Usage

`LANG=ru_RU.utf8 ./guesser`

`LANG=en_US.utf8 ./guesser`

# Clean

`make gitclean`

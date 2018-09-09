CXX=g++
#CC=/opt/djgpp/bin/i586-pc-msdosdjgpp-g++
CC=/usr/bin/avr-gcc
CC=/usr/bin/gcc
CC=/home/ockert/djgpp/720/bin/i586-pc-msdosdjgpp-gcc
CXX=/usr/bin/avr-g++
CXX=/usr/bin/g++
CXX=/home/ockert/djgpp/720/bin/i586-pc-msdosdjgpp-g++

SRC=./src/a.cpp
BIN=./bin/a
LIBDIR=-L./lib/lib
INCDIR=-I./lib/include
LIBDIR=-L/home/ockert/hosts/dos/usr/lib -L./lib
INCDIR=-I/home/ockert/hosts/dos/usr/include -I./include

CFLAGS=$(LIBDIR) $(INCDIR) -DDUK_CMDLINE_CONSOLE_SUPPORT -DDUK_USE_DATE_FMT_STRFTIME  -lm -fpermissive


#LIBS= -ljsoncpp -lalpng -lalleg
LIBS= -ljsoncpp -lalpng -lalleg -lduktape++

#SRC=./src/duktape.c ./src/fileio.c ./src/duk_console.c ./src/a.cpp
SRC=./src/fileio.c ./src/duk_console.c ./src/a.cpp
BIN=./bin/a.out

CONFIGFILE=configfile
$(BIN): $(SRC)
	$(CXX) $(CFLAGS) $(SRC) $(LIBS) -o $(BIN)
.phony: clean
clean:
	rm ./bin/*

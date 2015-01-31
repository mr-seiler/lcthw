# default flags for non-dev builds
# ?, optimize, warnings, more warnings, use src/, ?, turn off debug output, and cli args
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNODEBUG $(OPTFLAGS)
# ?
LIBS=-ldl $(OPTLIBS)
# set the prefix dir for make install to this if one is not specified by the user
PREFIX?=/usr/local

# build list of source files from src/ and all dirs below src
SOURCES=$(wildcard src/**/*.c src/*.c)
# build list of object files from list of source files
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

# build list of test source files from test dir w/ _test postfix
TEST_SRC=$(wildcard tests/*_test.c)
# build list of test executables from list of test source files
TESTS=$(patsubst %.c,%,$(TEST_SRC))

# CHANGE THIS - name of library to produce from source
TARGET=build/libCHANGE_ME.a
# in case the library needs a different extension (don't understand this yet)
SO_TARGET=$(patsub %.a,%.so,$(TARGET))

# by default, build release versions of library and run tests
all: $(TARGET) $(SO_TARGET) tests

# when `make dev`, do `make all` with alternate CFLAGS
dev: CFLAGS=-g -Wall -Wextra -Isrc $(OPTFLAGS)
dev: all

# fPIC apparently stands for "position independent code", and according to the
# gcc manpage the option only makes a difference on m68k, PowerPC and SPARC.
# So why we should include the option in a generic template makefile I don't know
# And I have no idea what "ar rcs" and "ranlib" do.
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

# still have no idea
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

# ensures that output dirs exist
build:
	@mkdir -p build
	@mkdir -p bin

# build and run unit tests
.PHONY tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

# run in valgrind w/ logging (no idea how it works)
valgrind:
	VALGRIND="valgrind --log-file=~/tmp/valgrind-%p.log" $(MAKE)

# stay tidy
clean:
	# delete all built .o and tests runnables
	rm -rf build $(OBJECTS) $(TESTS)
	# remove test log
	rm -f tests/tests.log
	# whatever. Why two different syntax for find + rm?
	find . -name "*.gc*" -exec rm {} \;
	# apparently left behind by Xcode, which means we don't need it
	rm -rf `find . -name "*.dSYM" -print`

# for `make install`
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# check for iffy c functions in src
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions:
	@egrep $(BADFUNCS) $(SOURCES) || true

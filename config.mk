# version
VERSION = 1.0

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\"
CFLAGS   = -pedantic -Wall

# compiler and linker
CC = cc

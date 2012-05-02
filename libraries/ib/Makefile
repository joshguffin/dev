# set the IBLIB environment variable to point to the libraries directory
# the default is the current directory (gitroot/libraries)
IBLIB ?= ..

include $(IBLIB)/../Makefile.first

# IB Library 
IBLIB_SRC = $(wildcard $(IBLIB)/ib_files/PosixSocketClient/*.cpp $(IBLIB)/ib_files/Shared/*.cpp)
IBLIB_OBJ = $(IBLIB_SRC:.cpp=.o)
IBLIB_OUT = $(IBLIB)/lib/lib_ib.a

$(IBLIB_OUT): $(IBLIB_OBJ)
	ar rcs $(IBLIB_OUT) $(IBLIB_OBJ)

all: $(IBLIB_OBJ)

clean:
	rm -f $(IBLIB_OBJ) $(IBLIB_OUT)


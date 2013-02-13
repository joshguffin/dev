include $(CPPROOT)/Makefile.first

portfolio_OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
portfolio_LIBRARIES = system data string
#portfolio_LDFLAGS = -lboost_program_options
APPPROGS += portfolio

include $(CPPROOT)/Makefile.last


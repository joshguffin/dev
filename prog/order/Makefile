include $(CPPROOT)/Makefile.first

order_OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
order_LIBRARIES = system data string
#order_LDFLAGS = -lboost_program_options
APPPROGS += order

include $(CPPROOT)/Makefile.last


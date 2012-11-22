include $(CPPROOT)/Makefile.first

sample_OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
sample_LIBRARIES = ibwrap
#sample_LDFLAGS = -lboost_program_options
APPPROGS += sample

include $(CPPROOT)/Makefile.last


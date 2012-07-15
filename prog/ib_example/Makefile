include $(CPPROOT)/Makefile.inc

sampleSOURCES = $(wildcard *.cpp)
sampleOBJECTS = $(patsubst %.cpp,%.o,$(sampleSOURCES))

%.o: %.cpp
	$(CXX) $(INCLUDES) $(USERCPPFLAGS) $(CCFLAGS) -c $*.cpp -o $@
	$(CXX) $(INCLUDES) $(USERCPPFLAGS) $(CCFLAGS) -MM -c $*.cpp -o $*.d

# for each .o file, append .d to the list $(..) = foo.o => foo.o foo.d
-include $(sampleOBJECTS:.o=.d)

sample: $(sampleOBJECTS)
	$(CXX) $(INCLUDES) $(LIBS) $(USERCPPFLAGS) $(LDFLAGS) -o $@ $(sampleOBJECTS)

APPROGS += sample

clean:
	rm -f sample *.o


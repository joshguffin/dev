include $(CPPROOT)/Makefile.inc

USERCPPFLAGS=-DIB_USE_STD_STRING -Wall -Wno-switch

sampleOBJECTS = $(patsubst %.c,%.o,$(wildcard *.cpp))

$(sampleOBJECTS):
	$(CXX) $(INCLUDES) $(LIBS) $(CCFLAGS) -c $< -o $@

sample:
	$(CXX) $(INCLUDES) $(LIBS) $(USERCPPFLAGS) $(LDFLAGS) -o $@ $(sampleOBJECTS)


clean:
	rm -f $(TARGET) *.o


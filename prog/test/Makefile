include $(CPPROOT)/Makefile.inc

################################################################################
string_testSOURCES = $(CPPROOT)/library/string/integertostring_test.cpp
string_testOBJECTS = $(patsubst %.cpp,%.o,$(string_testSOURCES))

%.o: %.cpp
	$(CXX) $(INCLUDES) $(USERCPPFLAGS) $(CCFLAGS) -c $*.cpp -o $@
	$(CXX) $(INCLUDES) $(USERCPPFLAGS) $(CCFLAGS) -MM -c $*.cpp -o $*.d

# for each .o file, append .d to the list $(..) = foo.o => foo.o foo.d
-include $(string_testOBJECTS:.o=.d)

string_test: $(string_testOBJECTS)
	$(CXX) $(INCLUDES) $(LIBS) $(USERCPPFLAGS) $(LDFLAGS) -lboost_unit_test_framework -o $@ $(string_testOBJECTS)

APPROGS += string_test

clean:
	rm -f string_test *.o

include $(CPPROOT)/Makefile.first

# populate the LIBRARIES variable
include $(CPPROOT)/library/Makefile.libraries

ALL_TEST_SOURCES=
###################################################################################
# Look through each library for *_test.cpp files and create a target for it
###################################################################################
define ADD_TEST_SOURCES
	$(eval $(1)_test_SOURCES=$(wildcard $(CPPROOT)/library/$(1)/*_test.cpp))
	$(eval TESTPROGS=$(TESTPROGS) $($(1)_test_SOURCES))
	$(eval ITEMS=$(foreach src, $($(1)_test_SOURCES), $(shell basename $(src:%.cpp=%))))
	$(eval TESTPROGSOURCES=$(TESTPROGSOURCES) "\n$(1)\t: $(ITEMS)")
endef

$(foreach lib, $(LIBRARIES), $(eval $(call ADD_TEST_SOURCES,$(lib))))

include $(CPPROOT)/Makefile.last

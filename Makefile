SUBMISSION = game
BUILDDIR   = build
EXECUTABLE = $(SUBMISSION)
SOURCES    = $(wildcard *.cpp)
OBJECTS    = $(patsubst %,$(BUILDDIR)/%,${SOURCES:.cpp=.o})
CXX        = clang++
ASANFLAGS  = -fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls
WARNINGS   = -Wall -Wextra -pedantic -ansi -Wno-unused-parameter -Wpedantic \
  -Wfloat-equal -Wshadow -Wsign-conversion \
  -Wsign-compare -Wpointer-arith -Wdeprecated
ERRORS 	   = -Werror=old-style-cast -Werror=non-virtual-dtor \
  -Werror=array-bounds -Werror=uninitialized \
  -Werror=format -Werror=format-nonliteral -Werror=float-equal \
  -Werror=delete-non-virtual-dtor -Werror=return-type
CXXFLAGS   = $(WARNINGS) $(ERRORS) $(ASANFLAGS) -g -c -std=c++17 -fsanitize=address -o
LDFLAGS    = $(ASANFLAGS)
LDLIBS     =
#-------------------------------------------------------------------------------

all: builddir $(EXECUTABLE)
#make executable
noasan: CXXFLAGS = $(WARNINGS) $(ERRORS) -g -c -std=c++17 -o
noasan: LDFLAGS = 

noasan: clean all

release : CXXFLAGS := -D RELEASE $(CXXFLAGS)
release : all

builddir:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: %.cpp
	@echo [CXX] $<
	@$(CXX) $(CXXFLAGS) $@ $< -MMD -MF ./$@.d

#link Objects
$(EXECUTABLE) : $(OBJECTS)
	@echo [LD] $@
	@$(CXX) -o $@ $^ $(LDFLAGS)

#make clean
clean:
	rm -f ./*.o
	rm -f ./*.o.d
	rm -f ./*.bin
	rm -rf ./$(BUILDDIR)
	rm -f $(EXECUTABLE)


run: builddir $(EXECUTABLE)
	./$(EXECUTABLE) config/config01.json

bonus: builddir $(EXECUTABLE)
	./$(EXECUTABLE) config/config08_bonus.json

.PHONY: clean cleanw submission run

#The dependencies:
-include $(wildcard *.d)
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g
INCLUDES = -Isrc

TARGET = rpn_calculator

SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

OBJDIR = obj
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean

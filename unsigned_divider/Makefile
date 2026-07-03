SYSTEMC_HOME = /opt/systemc

CXX       = g++
CXXFLAGS  = -std=c++17 -Wall -I$(SYSTEMC_HOME)/include
LDFLAGS   = -L$(SYSTEMC_HOME)/lib -lsystemc

OBJDIR    = obj

SRC       = $(wildcard *.cpp)

OBJ       = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

TARGET    = divider_sim.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean

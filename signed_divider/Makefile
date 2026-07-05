SYSTEMC_HOME = /opt/systemc

CXX       = g++
CXXFLAGS  = -std=c++17 -Wall -I$(SYSTEMC_HOME)/include
LDFLAGS   = -L$(SYSTEMC_HOME)/lib -lsystemc

TARGET    = dividerSigned_sim.out

SRCS      = $(wildcard *.cpp) $(wildcard unsigned_divider/*.cpp)

OBJDIR    = obj
OBJS      = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRCS)))

all: $(OBJDIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: part1/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET) *.vcd

.PHONY: all clean

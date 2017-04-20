CXX = g++
TARGET = memfrag

all: $(TARGET)


$(TARGET): $(patsubst  %.cpp,%.o,$(wildcard   *.cpp))
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) -c -MD $<

include $(wildcard   *.d)



clean:
	rm -rf $(TARGET) *.o *.d

.PHONY: all clean

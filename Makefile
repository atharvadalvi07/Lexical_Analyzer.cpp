CC=g++
CFLAGS=-std=c++11
TARGET=dcooke_analyzer

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	rm -f $(TARGET)

test: $(TARGET)
	./$(TARGET) test_input.dc

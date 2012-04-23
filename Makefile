TARGET  := r
WARN    := -Wall
OFLAGS  := -O2
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
CC      := g++

C_SRCS      = $(wildcard *.cpp)
OBJ_FILES   = $(C_SRCS:.cpp=.o)

%o: %cpp
	@echo "Compiling "$<"..."
	$(CC) -c $(OFLAGS) $< -o $@

$(TARGET): $(OBJ_FILES)
	@echo "Linking..."
	$(CC)  $(OFLAGS) $(LDFLAGS) -o $@ $(OBJ_FILES)
	@echo "Done."

all: ${TARGET}

clean:
	@echo "Cleaning..."
	rm -rf *.o

mrproper: clean
	rm -rf ${TARGET}

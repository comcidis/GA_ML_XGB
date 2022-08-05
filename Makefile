EXECUTABLE  := GA-DL.exe

C_SOURCE=$(wildcard src/*.cpp)
HEADERS = $(wildcard includes/*.h)

OBJS=$(subst .cpp,.o,$(subst src,bin,$(C_SOURCE)))

CC = g++

CC_FLAGS += -W         \

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJS)
	@ echo ' '
	@ echo 'Building binary using G++ linker: $@'
	$(CC) $(CCFlags) -o $@  $^
	@ echo 'Finished building binary: $@'
	@ echo ' '

bin/%.o: src/%.cpp includes/%.h 
	$(CC) -o $@ -c $< $(CCFlags)

bin/%.o: src/%.cpp
	$(CC) -o $@ -c $< $(CCFlags)

clean:
	rm -rf $(EXECUTABLE) $(OBJS) *.linkinfo
# 	@rmdir bin

# dir:
# 	@mkdir bin

.PHONY: all clean

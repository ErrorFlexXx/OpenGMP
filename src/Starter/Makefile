## Detect the current operating system
ifeq ($(OS),Windows_NT)
	CC = mingw32-g++
	RESC = mingw32-windres
	CFLAGS += -D WIN32
		ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		CFLAGS += -D AMD64
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			CFLAGS += -D AMD64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			CFLAGS += -D IA32
		endif
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC = i686-w64-mingw32-g++
		RESC = i686-w64-mingw32-windres
		CFLAGS += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		CFLAGS += -D OSX
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		CFLAGS += -D AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		CFLAGS += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		CFLAGS += -D ARM
	endif
endif

HEADER_FILES = 
OBJECT_FILES = starter.o
EXE_FILE = Starter.exe
#CC= i686-w64-mingw32-g++
CFLAGS = -Wall -O
LFLAGS = -static-libstdc++ -static-libgcc -mwindows

all: $(EXE_FILE)

resources.res : resources.rc
	$(RESC) resources.rc -O coff -o resources.res

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $<

$(EXE_FILE): $(OBJECT_FILES) resources.res
	$(CC) $(LFLAGS) $(OBJECT_FILES) resources.res -o $(EXE_FILE) -lpsapi

clean:
ifeq ($(OS),Windows_NT)
	del /F $(OBJECT_FILES) $(EXE_FILE) resources.res
else
	rm -f $(OBJECT_FILES) $(EXE_FILE) resources.res
endif

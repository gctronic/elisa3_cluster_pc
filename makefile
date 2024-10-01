# Specify compiler to be used
CXX = C:\\msys64\\ucrt64\\bin\\gcc.exe
CXXFLAGS += -g

# Specify paths to headers
INCLUDES += -I ..\\elisa3_remote_library

# Specify paths to the libraries
LDFLAGS  += -L ..\\elisa3_remote_library\\bin\\Release

# Specify the link libraries
LLIBS    += -lelisa3_remote_library

# ... add other configs ...

all: main

main:
	$(CXX) $(CXXFLAGS) $(INCLUDES) main.c $(LDFLAGS) $(LLIBS) -o main

clean:
	rm main

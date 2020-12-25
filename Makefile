CXX=g++
SRC=./src/*
CXXFLAGS=-shared -I$(IDIR) $(SRC) -fPIC -o $(TARGET)
IDIR=./include
BDIR=./bin
TARGET=$(BDIR)/libvk.so

all: clean lib

lib:
	@$(CXX) $(CXXFLAGS)

clean:
	@rm -f $(TARGET)

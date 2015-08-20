CFLAGS=-Wall -O3
DMDFLAGS=-release -O -inline -noboundscheck
LDCFLAGS=-O3 -release
GDCFLAGS=-O3
RUSTFLAGS=-C opt-level=3 -C debuginfo=0 -Z no-landing-pads
NIMFLAGS=c -d:release --checks=off
GOFLAGS=build
CC=gcc
CXX=g++
CLANGCC=clang
CLANGCXX=clang++
RUST=rustc
DMD=dmd
LDC=ldc
GDC=gdc
NIM=nim
GO=go

tester:
	mkdir -p bin
	$(CC) $(CFLAGS) ./src/tester.c -o tester
go: tester
	GOPATH=$(shell pwd) $(GO) $(GOFLAGS) go_lang
	mv go_lang ./bin/
gcc: tester
	$(CC) $(CFLAGS) ./src/c_lang.c -o ./bin/c_gcc
g++: tester
	$(CXX) $(CFLAGS) ./src/c++_lang.cpp -o ./bin/c++_gcc
clang: tester
	$(CLANGCC) $(CFLAGS) ./src/c_lang.c -o ./bin/c_clang
clang++: tester
	$(CLANGCXX) $(CLFAGS) ./src/c++_lang.cpp -o ./bin/c++_clang
rust: tester
	$(RUST) $(RUSTFLAGS) ./src/rust_lang.rs -o ./bin/rust_lang
dmd: tester
	$(DMD) $(DMDFLAGS) ./src/d_lang.d -of./bin/dmd_dlang
ldc: tester
	$(LDC) $(LDCFLAGS) ./src/d_lang.d -of./bin/ldc_dlang
gdc: tester
	$(GDC) $(GDCFLAGS) ./src/d_lang.d -o ./bin/gdc_dlang
nim: tester
	$(NIM) $(NIMFLAGS) ./src/nim_lang.nim
	mv ./src/nim_lang ./bin/
	$(RM) -rf ./src/{nimcache,*.o}
strip:
	strip -s -w ./bin/*
all: gcc g++ clang clang++ rust dmd ldc gdc nim strip
	$(RM) -rf ./bin/*.o
clean:
	$(RM) -rf bin tester

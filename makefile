all:
	mkdir -p build
	gcc -O2 main.c bytearray/bytearray.c -o build/file2array
win:
	mkdir -p build
	x86_64-w64-mingw32-gcc -O2 main.c bytearray/bytearray.c -o build/file2array

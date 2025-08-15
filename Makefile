all:
	mkdir -p build/
	g++ src/main.cc src/gen.cc -o build/penguin `pkg-config --cflags --libs Qt6Widgets`

clean:
	rm -rf build

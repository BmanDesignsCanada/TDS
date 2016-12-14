all:
	g++ pack.cxx -o pack
	g++ unpack.cxx -o unpack
clean:
	rm pack unpack

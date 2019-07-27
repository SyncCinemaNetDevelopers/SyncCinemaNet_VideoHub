

all:
	cd src;g++ main.cpp rtsp.cpp utils/exception.cpp;cd ..
	mkdir
	mv src/a.out bin/
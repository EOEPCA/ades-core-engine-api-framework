CFLAGS= -Iinclude  -I/opt/zoo-project/zoo-project/zoo-kernel -L/var/lib64   `cgicc-config --cxxflags`   -I`cgicc-config --includedir` -L`cgicc-config  --libdir` -I/usr/include/
all:
	mkdir -p  build
	g++ -std=c++17 src/zoo/argolib.cpp  -shared -fpic -obuild/libargolib.so
	g++ -std=c++17 src/zoo/argo.cpp ${CFLAGS} -lcgicc -ljson-c -shared -fpic  -lpthread -ldl -lzoo_service -obuild/argo.zo
clean:
	rm -fvR build/*
package:

build:

install:
	cp build/argo.zo /zooservices/
	cp src/zoo/argo.zcfg /zooservices/
	cp build/libargolib.so /zooservices/
	cp src/zoo/argo.cwl /zooservices/
#
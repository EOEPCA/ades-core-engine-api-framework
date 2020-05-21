CFLAGS= -Iinclude  -I/opt/zoo-project/zoo-project/zoo-kernel -L/var/lib64   `cgicc-config --cxxflags`   -I`cgicc-config --includedir` -L`cgicc-config  --libdir` -I/usr/include/
all:
	mkdir -p  build
	#g++ -std=c++17 argolib.cpp  -shared -fpic -obuild/libargo_interface.so
	g++ -std=c++17 argo.cpp ${CFLAGS} -lcgicc -ljson-c -shared -fpic  -lpthread -ldl -lzoo_service -obuild/argo.zo
clean:
	rm -fvR build/*
package:

build:

install:
	cp build/argo.zo /opt/t2service/
	cp argo.zcfg /opt/t2service/
	#cp build/libargo_interface.so /opt/t2service/
	cp argo.cwl /opt/t2service/

local:
	cp build/argo.zo /zooservices/
	cp argo.zcfg /zooservices
	#cp build/libargo_interface.so /zooservices
	cp argo.cwl /zooservices



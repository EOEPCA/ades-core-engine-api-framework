FROM proc-comm-zoo:1.0

COPY assets/main.cfg /opt/t2service/main.cfg
COPY assets/oas.cfg /opt/t2service/oas.cfg

COPY src/zoo /tmp/zoo
RUN cd /tmp/zoo && make && make install && rm -fvR /tmp/zoo

COPY build/3ty/proc-comm-lib-argo/proc-comm-lib-argo-build/libeoepcaargo.so /opt/t2service/libeoepcaargo.so
COPY build/libargo_interface.so /opt/t2service/libargo_interface.so

#sudo docker run --rm  -d --name zoo -p 7777:80  -v   eoepca-ades-core:1.0
#sudo docker run --rm  -d --name zoo -p 7777:80  -v $PWD:/project  eoepca-ades-core:1.0

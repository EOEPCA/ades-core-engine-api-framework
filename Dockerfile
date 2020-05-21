FROM proc-comm-zoo:1.0

COPY assets/main.cfg /opt/t2service/main.cfg
COPY assets/oas.cfg /opt/t2service/oas.cfg

#COPY src/zoo /tmp/zoo
#RUN cd /tmp/zoo && make && make install && rm -fvR /tmp/zoo && chmod +x /opt/t2scripts/entrypoint.sh
RUN chmod +x /opt/t2scripts/entrypoint.sh

COPY src/templates/template.cpp /opt/t2template/template.cpp
COPY src/templates/Makefile /opt/t2template/Makefile
COPY src/deployundeploy/zoo/build/libepcatransactional.zo /opt/t2service/
COPY src/deployundeploy/zoo/*.zcfg /opt/t2service/
COPY src/templates/libinterface.so /opt/t2libs/libinterface.so
COPY build/3ty/proc-comm-lib-ows-1.03/libeoepcaows.so /opt/t2libs/
COPY build/3ty/proc-comm-lib-argo/proc-comm-lib-argo-build/libeoepcaargo.so /opt/t2service/libeoepcaargo.so
COPY build/libargo_interface.so /opt/t2service/libargo_interface.so

#sudo docker run --rm  -d --name zoo -p 7777:80    eoepca-ades-core:1.0
#sudo docker run --rm  -d --name zoo -p 7777:80  -v $PWD:/project  eoepca-ades-core:1.0
#alias ll='ls -ltr'
# docker exec -ti -e COLUMNS="`tput cols`" -e LINES="`tput lines`" zoo  bash
#alias ll='ls -ltr'
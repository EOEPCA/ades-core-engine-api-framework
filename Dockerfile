FROM proc-comm-zoo:1.0

COPY assets/main.cfg /opt/t2service/main.cfg
COPY assets/oas.cfg /opt/t2service/oas.cfg

COPY src/zoo /tmp/zoo
RUN cd /tmp/zoo && make && make install

#sudo docker run --rm  -d --name zoo -p 7777:80 eoepca-ades:1.0

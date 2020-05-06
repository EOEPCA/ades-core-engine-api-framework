FROM proc-comm-zoo:1.0

COPY assets/main.cfg /opt/t2service/main.cfg
COPY assets/oas.cfg /opt/t2service/oas.cfg

#sudo docker run --rm  --env FOLDER=${FOLDER} --name zoo -p 7777:80 -d   -v $PWD:/work ades:1.0
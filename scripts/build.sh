#!/usr/bin/env bash

#rm -fvR build

if [ -z "${BUILDER_DOCKERIMAGE}" ]; then
  BUILDER_DOCKERIMAGE='eoepca/eoepca-build-cpp:1.0'
fi

if [ -z "${CMAKERELEASE}" ]; then
  CMAKERELEASE='Release'
fi

if [ -z "${LOCAL_IMAGE_NAME}" ]; then
  LOCAL_IMAGE_NAME='eoepca-ades-core:1.0'
fi

mkdir -p build

docker run --rm -ti -v $PWD:/project/ -w /project/build/ ${BUILDER_DOCKERIMAGE} cmake -DCMAKE_BUILD_TYPE=${CMAKERELEASE} -G "CodeBlocks - Unix Makefiles" ..
if [ $? -ne 0 ]; then
  echo "CMAKE release ${CMAKERELEASE} failed"
  exit 2
fi

#docker run --rm -ti -v $PWD:/project/ -w /project/build/ ${BUILDER_DOCKERIMAGE} make eoepcaargo
#if [ $? -ne 0 ]; then
#  echo "make eoepcaargo failed"
#  exit 2
#fi
#
#docker run --rm -ti -v $PWD:/project/ -w /project/build/ ${BUILDER_DOCKERIMAGE} make  sources
#if [ $? -ne 0 ]; then
#  echo "make sources failed"
#  exit 2
#fi

docker run --rm -ti -v $PWD:/project/ -w /project/build/ ${BUILDER_DOCKERIMAGE} make  argo_interface
if [ $? -ne 0 ]; then
  echo "make sources failed"
  exit 2
fi


exit;

HERE=$PWD
cd build/3ty/proc-comm-zoo/proc-comm-zoo/
chmod +x ./scripts/build.sh
./scripts/build.sh

cd $HERE
docker build --rm -t ${LOCAL_IMAGE_NAME} .

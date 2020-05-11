#!/usr/bin/env bash
#rm -fvR build
if [ -z "${BUILDER_DOCKERIMAGE}" ]; then
  BUILDER_DOCKERIMAGE='eoepca/eoepca-build-cpp:1.0'
fi
if [ -z "${CMAKERELEASE}" ]; then
  CMAKERELEASE='Debug'
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
docker run --rm -ti -v $PWD:/project/ -w /project/build/ ${BUILDER_DOCKERIMAGE} make eoepcaargo sources argo_interface ades_main

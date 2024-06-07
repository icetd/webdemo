#! /usr/bin/bash
CURRENT_DIR=$(pwd)
POCO_VERSION=1.13.3-release
POCO_SRC=poco-poco-${POCO_VERSION}
POCO_SRC_DIR=${CURRENT_DIR}/thirdparty/${POCO_SRC}
POCO_URL=https://github.com/pocoproject/poco/archive/refs/tags/poco-${POCO_VERSION}.tar.gz
POCO_PREFIX=${CURRENT_DIR}/thirdparty/poco

mkdir -p ${CURRENT_DIR}/thirdparty
cd ${CURRENT_DIR}/thirdparty

if [ ! -d "${POCO_PREFIX}" ]
then
    (wget -O "${POCO_SRC}.tar" ${POCO_URL} \
        && tar -xf "${POCO_SRC}.tar") || exit
    rm -f "${POCO_SRC}.tar"
else
    echo "already build poco"
fi

if [ ! -d "${POCO_PREFIX}" ]
then
    cd ${POCO_SRC_DIR}
    (cmake -DCMAKE_INSTALL_PREFIX=${POCO_PREFIX} .) || exit
    (make -j8 && make install) || exit
    cd ${CURRENT_DIR}
    (rm -rf "${POCO_SRC_DIR}") || exit
else
    echo "already build poco"
fi

sed -i '/LD_LIBRARY_PATH/d' ~/.bashrc
source ~/.bashrc

echo export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${POCO_PREFIX}/lib >> ~/.bashrc
source ~/.bashrc

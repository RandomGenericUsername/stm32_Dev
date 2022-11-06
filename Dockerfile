from ubuntu:20.04

RUN mkdir -p /project/binaries && \
    mkdir -p /project/source-files && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y gcc g++ gcc-arm-none-eabi gdb-multiarch cmake make

WORKDIR /project

ADD /Build /project/source-files/Build
ADD /Core /project/source-files/Core
ADD /Scripts /projectsource-files/Scripts
COPY Makefile /project/source-files

RUN cd /project/source-files/ && \
    make clean && \
    make all && \
    cd Build/bins && \
    cp mainProject.elf mainProject.bin mainProject.hex ../../../binaries





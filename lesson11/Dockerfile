#FROM debian:10
FROM ubuntu:18.04

RUN dpkg --add-architecture i386
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y wget
#RUN apt-get install -y libcanberra-gtk-module
RUN apt-get install -y \
    libsm6:i386 \
    libxrender1:i386 \
    libcanberra-gtk-module:i386 \
    libjpeg62:i386

RUN wget -q http://mirrors.edge.kernel.org/ubuntu/pool/main/libp/libpng/libpng12-0_1.2.54-1ubuntu1.1_i386.deb
RUN dpkg -i libpng12-0_1.2.54-1ubuntu1.1_i386.deb
#    && rm -rf /var/lib/apt/lists/*

#WORKDIR /usr/src/cheddar
WORKDIR /root

#RUN curl http://beru.univ-brest.fr/~singhoff/cheddar/Cheddar-3.1-linux32-bin.tar.gz -o Cheddar-3.1-linux32-bin.tar.gz

COPY cheddar.bash .
COPY Cheddar-3.1-linux32-bin.tar.gz .
#RUN mkdir /usr/src/cheddar
RUN tar -xvzf Cheddar-3.1-linux32-bin.tar.gz -C /usr/src
RUN mv /usr/src/Cheddar-3.1-Linux32-bin /usr/src/cheddar

ENV CHEDDAR_INSTALL_PATH=usr/src/cheddar/
ENV PATH=$GNAT_DIR/bin:$CHEDDAR_INSTALL_PATH/bin/linux32:/usr/bin/svn:$PATH
ENV LIBRARY_PATH=$CHEDDAR_INSTALL_PATH/lib/linux32:$CHEDDAR_INSTALL_PATH/lib/linux32/gtk-2.0/modules:/lib/i386-linux-gnu/:/usr/lib/i386-linux-gnu:$LIBRARY_PATH
ENV LD_LIBRARY_PATH=$LIBRARY_PATH:$LD_LIBRARY_PATH

#WORKDIR /root
#COPY ./task/ .
WORKDIR /usr/src/cheddar

CMD ./cheddar
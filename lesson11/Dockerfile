FROM debian:10

RUN dpkg --add-architecture i386
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y \
    libc6-i386 \
    libsm6:i386 \
    libxrender1:i386 \
    libcanberra-gtk-module:i386
#RUN apt-get install -y wget

WORKDIR /root

#RUN curl http://beru.univ-brest.fr/~singhoff/cheddar/Cheddar-3.1-linux32-bin.tar.gz -o Cheddar-3.1-linux32-bin.tar.gz

COPY Cheddar-3.1-linux32-bin.tar.gz .
RUN tar -xvzf Cheddar-3.1-linux32-bin.tar.gz -C /usr/local
ENV CHEDDAR_INSTALL_PATH=/usr/local/Cheddar-3.1-Linux32-bin/
ENV PATH=$CHEDDAR_INSTALL_PATH:$PATH
ENV PATH=$GNAT_DIR/bin:$CHEDDAR_INSTALL_PATH/bin/linux32:/usr/bin/svn:$PATH
ENV LIBRARY_PATH=$CHEDDAR_INSTALL_PATH/lib/linux32:$CHEDDAR_INSTALL_PATH/lib/linux32/gtk-2.0/modules:/lib/i386-linux-gnu/:/usr/lib/i386-linux-gnu:$LIBRARY_PATH
ENV LD_LIBRARY_PATH=$LIBRARY_PATH:$LD_LIBRARY_PATH
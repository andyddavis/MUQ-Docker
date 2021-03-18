FROM python:3

# Download boost, untar, setup install with bootstrap and only do the Program Options library, and then install
RUN cd /home && wget http://downloads.sourceforge.net/project/boost/boost/1.60.0/boost_1_60_0.tar.gz \
  && tar xfz boost_1_60_0.tar.gz \
  && rm boost_1_60_0.tar.gz \
  && cd boost_1_60_0 \
  && ./bootstrap.sh --prefix=/usr/local --with-libraries=system \
  && ./b2 install \
  && cd /home \
  && rm -rf boost_1_60_0

# Download Eigen
RUN git clone https://gitlab.com/libeigen/eigen.git

RUN mkdir root/src/ && \
    mkdir root/include

COPY _docker.cpp /root/src/
COPY include/comm.h /root/include/

RUN cd root/ && \
    g++ -o main -I /usr/local/include/ -I /eigen -I . -L /usr/local/lib/ src/_docker.cpp -lboost_system

ENV LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:/usr/local/lib"

CMD cd /root/ && \
    ./main

FROM ubuntu:focal

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    g++ \
    libboost-filesystem-dev \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/wallpaper

COPY src src
COPY CMakeLists.txt .

RUN mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make

RUN rm -rf src
RUN rm CMakeLists.txt

CMD [ "./build/wallpaper" ]

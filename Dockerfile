# Build stage
FROM ubuntu:focal AS build

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

# Production stage
FROM ubuntu:focal AS production

RUN apt-get update && apt-get install -y --no-install-recommends \
    libboost-filesystem-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/wallpaper

COPY --from=build /root/wallpaper/build build

CMD [ "build/wallpaper" ]

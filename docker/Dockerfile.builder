#ARG CUDA="11.7.0"
#ARG UBUNTU="20.04"
#ARG OPENCV="4.6.0"

FROM danger89/cmake:4.4 as cmake
FROM jamalabo1/entrance_monitor:thirdparty_bundler as thirdparty_bundler
FROM jamalabo1/entrance_monitor:gpu-opencv as project_builder
RUN apt-get update && apt-get install -y  build-essential libboost-all-dev libeigen3-dev pkg-config gdb && rm -rf /var/lib/apt/lists/*
COPY --from=thirdparty_bundler /opt/vcpkg /opt/vcpkg
COPY --from=thirdparty_bundler /opt/cppack /opt/cppack
COPY --from=cmake /usr/bin/cmake /usr/bin/cmake
COPY --from=cmake /usr/lib/x86_64-linux-gnu/cmake /usr/lib/x86_64-linux-gnu/cmake
COPY --from=cmake /usr/lib/x86_64-linux-gnu/libjsoncpp.so.24 /usr/lib/x86_64-linux-gnu/libjsoncpp.so.24
COPY --from=cmake /usr/share/cmake-3.18 /usr/share/cmake-3.18
COPY --from=cmake /usr/share/cmake /usr/share/cmake
ENV Msgpack_DIR=/opt/cppack
WORKDIR /
ARG CUDA_VERSION="11.7.0"
ARG UBUNTU="20.04"

FROM jamalabo1/entrance_monitor:thirdparty_bundler as thirdparty_bundler
FROM jamalabo1/entrance_monitor:gpu-opencv as gpu_opencv
#FROM danger89/cmake:4.4 as project_builder
FROM nvidia/cuda:${CUDA_VERSION}-cudnn8-devel-ubuntu${UBUNTU}
ENV DEBIAN_FRONTEND=noninteractive

#COPY --from=gpu_opencv /usr/lib/x86_64-linux-gnu/lib*.so /usr/lib/x86_64-linux-gnu/

RUN apt update && apt install -y --no-install-recommends  \
    build-essential \
    cmake \
    gcc \
    g++ \
    gdb \
    clang \
    ninja-build \
    autoconf \
    pkg-config \
    checkinstall \
    && rm -rf /var/lib/apt/lists/*

RUN apt update && apt install -y --no-install-recommends libavcodec-dev libavformat-dev libswscale-dev libboost-all-dev && rm -rf /var/lib/apt/lists/*
# copy opencv artifacts (bin,lib,headers) ## bin is not needed since it's used for linkage only.
COPY --from=gpu_opencv /usr/local/lib/libopencv*.a /usr/local/lib/
COPY --from=gpu_opencv /usr/local/lib/opencv4 /usr/local/lib/opencv4
COPY --from=gpu_opencv /usr/local/bin/opencv* /usr/local/bin/
COPY --from=gpu_opencv /usr/local/lib/cmake/opencv4 /usr/local/lib/cmake/opencv4
COPY --from=gpu_opencv /usr/local/include/opencv4 /usr/local/include/opencv4

#COPY --from=gpu_opencv /usr/local/cuda /usr/local/cuda
#COPY --from=gpu_opencv /usr/local/cuda-11.7 /usr/local/cuda-11.7
#COPY --from=gpu_opencv /usr/include/cudnn*.h /usr/include/


# copy vcpkg artifacts (thirdparty packages)
COPY --from=thirdparty_bundler /opt/vcpkg /opt/vcpkg
COPY --from=thirdparty_bundler /opt/cppack /opt/cppack

#COPY --from=cmake /usr/bin/cmake /usr/bin/cmake
#COPY --from=cmake /usr/lib/x86_64-linux-gnu/cmake /usr/lib/x86_64-linux-gnu/cmake
#COPY --from=cmake /usr/lib/x86_64-linux-gnu/libjsoncpp.so.24 /usr/lib/x86_64-linux-gnu/libjsoncpp.so.24
#COPY --from=cmake /usr/share/cmake-3.18 /usr/share/cmake-3.18
#COPY --from=cmake /usr/share/cmake /usr/share/cmake
ENV Msgpack_DIR=/opt/cppack
WORKDIR /
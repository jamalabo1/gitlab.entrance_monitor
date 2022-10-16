ARG CUDA_VERSION="11.7.0"
ARG UBUNTU="20.04"

FROM jamalabo1/entrance_monitor:thirdparty_bundler as thirdparty_bundler
FROM jamalabo1/entrance_monitor:gpu-opencv as gpu_opencv
FROM nvidia/cuda:${CUDA_VERSION}-cudnn8-devel-ubuntu${UBUNTU}
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends  \
    build-essential \
    gcc \
    g++ \
    gdb \
    clang \
    ninja-build \
    git \
    autoconf \
    pkg-config \
    checkinstall \
    software-properties-common \
    python-dev  \
    autotools-dev  \
    libicu-dev \
    libbz2-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - |  tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 6AF7F09730B3F0A4

RUN apt-get update && apt-get install -y --no-install-recommends cmake libavcodec-dev libavformat-dev libswscale-dev && rm -rf /var/lib/apt/lists/*

ARG BOOST_VERSION="1_80_0"

# install boost library
RUN wget -O boost_1_80_0.tar.gz https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz
RUN tar xzvf boost_1_80_0.tar.gz
RUN cd boost_1_80_0 && ./bootstrap.sh --prefix=/usr/local
RUN cd boost_1_80_0 && n=`cat /proc/cpuinfo | grep "cpu cores" | uniq | awk '{print $NF}'` && ./b2 --with=all -j $n install

RUN apt-get update && apt-get install -y zlib1g-dev

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
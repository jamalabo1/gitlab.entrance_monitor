FROM jamalabo1/entrance_monitor:builder as builder
RUN mkdir /home/project
WORKDIR /home/project
COPY . ./
RUN  cmake \
     -G Ninja \
     -D VCPKG_VERBOSE=ON \
     -D CMAKE_BUILD_TYPE=Release \
     -D CMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
     -D AZURE_SDK_DISABLE_AUTO_VCPKG=ON \
     -D CORE_USE_AZURE_KEYVAULT=ON \
     -B /home/project/build

ARG CMAKE_PROJECT_TARGET

RUN cmake --build /home/project/build --target $CMAKE_PROJECT_TARGET -j $(nproc)
RUN cmake --install /home/project/build --component $CMAKE_PROJECT_TARGET


FROM jamalabo1/entrance_monitor:runtime as runtime
COPY --from=builder /usr/local/bin /usr/local/bin

ARG PROJECT_TARGET
ARG CMAKE_PROJECT_TARGET

WORKDIR /usr/local/bin

ENV CMAKE_PROJECT_TARGET=${CMAKE_PROJECT_TARGET}

ENTRYPOINT "${CMAKE_PROJECT_TARGET}"

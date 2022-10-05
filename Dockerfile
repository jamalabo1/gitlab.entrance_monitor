
FROM jamalabo1/entrance_monitor:builder as builder
RUN mkdir /home/project
WORKDIR /home/project
COPY . ./
RUN  cmake  \
     -G Ninja \
     -D VCPKG_VERBOSE=ON \
     -D CMAKE_BUILD_TYPE=Debug \
     -D CMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
     -D AZURE_SDK_DISABLE_AUTO_VCPKG=ON \
     -D CORE_USE_AZURE_KEYVAULT=ON \
     -B /home/project/build

ARG CMAKE_PROJECT_TARGET

RUN cmake --build /home/project/build --target $CMAKE_PROJECT_TARGET -j $(nproc)


FROM jamalabo1/entrance_monitor:runtime as runtime
COPY --from=builder /home/project/build /home/project/build

ARG PROJECT_TARGET
ARG CMAKE_PROJECT_TARGET

WORKDIR /home/project/build/src/${PROJECT_TARGET}
#ENV PATH="/home/project/build/src/$(echo $ENV_PROJECT_TARGET | tr '-' '_'):${PATH}"
#ENTRYPOINT "/home/project/build/src/$(echo $ENV_PROJECT_TARGET | tr '-' '_')/"
ENTRYPOINT "${CMAKE_PROJECT_TARGET}"
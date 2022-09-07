
FROM jamalabo1/entrance_monitor:builder as builder
RUN mkdir /home/project
WORKDIR /home/project
COPY . ./
RUN  cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja -DVCPKG_VERBOSE=ON -DAZURE_SDK_DISABLE_AUTO_VCPKG=ON \
     -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
     -B /home/project/build

ARG PROJECT_TARGET
ENV ENV_PROJECT_TARGET=$PROJECT_TARGET
ENV CMAKE_PROJECT_TARGET="${ENV_PROJECT_TARGET}-standalone"

RUN cmake --build /home/project/build --target $(echo $CMAKE_PROJECT_TARGET | tr "-" "_") -j 6


FROM jamalabo1/entrance_monitor:runtime as runtime
COPY --from=builder /home/project/build /home/project/build

ARG PROJECT_TARGET
ENV ENV_PROJECT_TARGET=$PROJECT_TARGET
ENV CMAKE_PROJECT_TARGET="${ENV_PROJECT_TARGET}_standalone"

#WORKDIR /home/project/build/src/${ENV_PROJECT_TARGET}

#ENV PATH="/home/project/build/src/$(echo $ENV_PROJECT_TARGET | tr '-' '_'):${PATH}"
ENTRYPOINT "/home/project/build/src/$(echo $ENV_PROJECT_TARGET | tr '-' '_')/$(echo $CMAKE_PROJECT_TARGET | tr '-' '_')"
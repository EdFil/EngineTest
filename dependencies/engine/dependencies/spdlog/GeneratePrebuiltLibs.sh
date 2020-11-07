mkdir build
cd build
cmake ../source -DCMAKE_INSTALL_PREFIX:PATH=../generated -DSPDLOG_BUILD_SHARED=OFF -DSPDLOG_NO_EXCEPTIONS=ON
cmake --build . --target install --config Release
mkdir build
cd build
cmake ../source -DCMAKE_INSTALL_PREFIX:PATH=../generated
cmake --build . --target install --config Debug
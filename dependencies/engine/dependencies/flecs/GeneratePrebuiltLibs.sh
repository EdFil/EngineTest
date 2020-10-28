mkdir build
cd build
cmake ../source
cmake --build . --config Release
cmake --install . --config Release --prefix install
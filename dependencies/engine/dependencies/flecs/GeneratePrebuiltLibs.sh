mkdir build
cd build
cmake ../source
cmake --build . --config Debug
cmake --install . --config Debug --prefix ../generated
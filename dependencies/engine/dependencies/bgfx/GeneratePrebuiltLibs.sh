mkdir build
cd build
cmake ../source -DBGFX_BUILD_TOOLS=OFF -DBGFX_BUILD_EXAMPLES=OFF -DBGFX_LIBRARY_TYPE="STATIC"
cmake --build . --config Debug
cmake --install . --config Debug --prefix ../generated
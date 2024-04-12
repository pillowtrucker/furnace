cmake -GNinja -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_GUI=ON -DSYSTEM_FFTW=ON -DSYSTEM_FMT=ON -DSYSTEM_LIBSNDFILE=ON -DSYSTEM_RTMIDI=ON -DSYSTEM_SDL2=ON -DSYSTEM_ZLIB=ON -DSYSTEM_PORTAUDIO=ON -DWITH_PORTAUDIO=ON -DWITH_RENDER_SDL=ON -DWITH_RENDER_OPENGL=ON
cmake --build build --parallel 8

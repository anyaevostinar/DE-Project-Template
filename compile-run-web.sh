emcc -std=c++17 -IEmpirical/include/ -Isignalgp-lite/include/ -Os --js-library Empirical/include/emp/web/library_emp.js -s EXPORTED_FUNCTIONS="['_main', '_empCppCallback', '_empDoCppCallback']" -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s NO_EXIT_RUNTIME=1 web.cpp -o de_web.js
python3 -m http.server

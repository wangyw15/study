cmake_minimum_required (VERSION 3.10)
project (midi_music)

add_executable (midi_music src/main.cpp)
target_link_libraries (midi_music winmm)
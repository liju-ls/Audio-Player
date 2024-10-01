cmake_minimum_required(VERSION 3.5)

project("my project")

link_directories(app ${CMAKE_SOURCE_DIR}/lib)


add_executable(app main.cpp fileHandling/discoverSongs.cpp fileHandling/folderOpen.cpp fileHandling/listSongs.cpp ui/playAndPause.cpp ui/progressBar.cpp)

set_target_properties(app PROPERTIES WIN32 $<CONFIG:Release>)

target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include)


target_link_libraries(app sfml-system sfml-window sfml-audio sfml-graphics ole32 uuid)
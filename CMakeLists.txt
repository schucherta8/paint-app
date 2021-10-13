#TODO: ONLY TESTED WITH MAC OS, MAYBE CHANGE IT TO DEAL WITH LINUX OR WINDOWS?
cmake_minimum_required(VERSION 3.15)
project(paint_with_friends VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE "Debug")

#Change <sfml root prefix>
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

find_package(SFML 2.4 COMPONENTS system window graphics network REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(Catch2 REQUIRED)
#Needed it for Tests to run
include_directories("./include/")
include_directories("/usr/include/")
include_directories("./lib")
add_executable(app
        src/main.cpp
        src/App.cpp
        src/Command.cpp
        src/Draw.cpp
        src/Clear_Canvas.cpp
        src/nuklear.cpp
		src/UDPNetworkServer.cpp
		src/UDPNetworkClient.cpp
		src/Chat.cpp
		src/CommandParser.cpp
		src/Graphics_Manager.cpp)
add_executable(app_test
        ./src/App.cpp
        ./src/Command.cpp
        ./src/Draw.cpp
		./src/Clear_Canvas.cpp
		./src/UDPNetworkServer.cpp
		./src/UDPNetworkClient.cpp
        ./tests/main_test.cpp
        src/nuklear.cpp
		src/Chat.cpp
		src/CommandParser.cpp
		src/Graphics_Manager.cpp
        src/Command_Stream.cpp
        src/Mock_Command.cpp)

target_link_libraries(app
        sfml-graphics
        sfml-system
        sfml-window
		sfml-network
        OpenGL::GL
	-lpthread)
target_link_libraries(app_test
        sfml-graphics
        sfml-window
        sfml-system
		sfml-network
        OpenGL::GL
	-lpthread)
target_include_directories(app PRIVATE
        include/)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("SecuritySystem")
find_package( OpenCV REQUIRED )

add_executable(exec FrameChecker.cc Keyboard.cc Memory.cc Relay.cc Light.cc WebServer.cc  Temperature.cc Camera.cc  Dma.cc Main.cc)
target_link_libraries(exec ${OpenCV_LIBS} )
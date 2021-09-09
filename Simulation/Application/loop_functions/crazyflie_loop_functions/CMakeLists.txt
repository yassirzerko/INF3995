ExternalProject_Add(project_libsioclient
  GIT_REPOSITORY https://github.com/socketio/socket.io-client-cpp.git
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libsioclient
  CONFIGURE_COMMAND ""
  BUILD_COMMAND cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON ../project_libsioclient
  INSTALL_COMMAND make install
  PREFIX=${CMAKE_CURRENT_BINARY_DIR}/libsioclient
)
ExternalProject_Get_Property(project_libsioclient install_dir)

set(crazyflie_loop_functions_SOURCES
  crazyflie_loop_functions.h
  crazyflie_loop_functions.cpp)

add_library(crazyflie_loop_functions MODULE
  ${crazyflie_loop_functions_SOURCES})

add_library(libsioclient STATIC IMPORTED)

set_property(TARGET libsioclient PROPERTY IMPORTED_LOCATION
   /usr/local/lib/libsioclient.a)

add_dependencies(libsioclient project_libsioclient)

include_directories(${install_dir}/src/project_libsioclient/src)

target_link_libraries(crazyflie_loop_functions
  libsioclient
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_crazyflie)

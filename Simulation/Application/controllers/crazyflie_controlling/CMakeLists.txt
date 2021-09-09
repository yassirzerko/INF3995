add_library(battery_sensor SHARED battery_sensor.h)
add_library(distance_sensors_manager SHARED distance_sensors_manager.h distance_sensors_manager.cpp)
add_library(commander SHARED commander.h commander.cpp)
add_library(wall_follower SHARED wall_follower.h wall_follower.cpp)
add_library(return_to_base SHARED return_to_base.h return_to_base.cpp)
add_library(exploration SHARED exploration.h exploration.cpp)
add_library(crazyflie_controlling SHARED crazyflie_controlling.h crazyflie_controlling.cpp)
target_link_libraries(crazyflie_controlling
  exploration
  return_to_base
  wall_follower
  commander
  distance_sensors_manager
  battery_sensor
  argos3core_simulator
  argos3plugin_simulator_crazyflie
  argos3plugin_simulator_genericrobot)

cmake_minimum_required(VERSION 3.8)
project(turtlesim_catch_them_all_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(my_robot_interfaces REQUIRED)

include_directories(include)

add_executable(turtle_spawner src/turtle_spawner.cpp src/TurtleSpawnerNode.cpp)
ament_target_dependencies(turtle_spawner rclcpp turtlesim my_robot_interfaces)
add_executable(turtle_controller src/turtle_controller.cpp src/TurtleControllerNode.cpp)
ament_target_dependencies(turtle_controller rclcpp turtlesim geometry_msgs my_robot_interfaces)

install(TARGETS

  turtle_spawner
  turtle_controller

  DESTINATION lib/${PROJECT_NAME}


)


ament_package()

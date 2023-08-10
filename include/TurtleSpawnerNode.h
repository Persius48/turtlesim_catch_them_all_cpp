#ifndef TURTLESPAWNERNODE_H
#define TURTLESPAWNERNODE_H

#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "my_robot_interfaces/msg/turtle.hpp"
#include "my_robot_interfaces/msg/turtle_array.hpp"
#include "my_robot_interfaces/srv/catch_turtle.hpp"

class TurtleSpawnerNode : public rclcpp::Node
{
public:
    TurtleSpawnerNode();

private:
    void publishAliveTurtles();

    void callbackCatchTurtle(const my_robot_interfaces::srv::CatchTurtle::Request::SharedPtr request,
                             const my_robot_interfaces::srv::CatchTurtle::Response::SharedPtr response);

    // returns random double number in range [0.0, 1.0)
    double randomDouble();

    void spawnNewTurtle();

    void callSpawnTurtleService(const std::string& name, double x, double y, double theta);

    void callKillTurtleService(std::string turtle_name);


    std::string turtle_name_prefix_;
    double spawn_frequency_;
    int turtle_counter_;
    std::vector<my_robot_interfaces::msg::Turtle> alive_turtles_;

    rclcpp::Publisher<my_robot_interfaces::msg::TurtleArray>::SharedPtr alive_turtles_publisher_;
    rclcpp::Service<my_robot_interfaces::srv::CatchTurtle>::SharedPtr catch_turtle_service_;
    rclcpp::TimerBase::SharedPtr publish_alive_turtles_timer_;
    rclcpp::TimerBase::SharedPtr spawn_turtle_timer_;

    std::vector<std::shared_ptr<std::thread>> spawn_turtle_threads_;
    std::vector<std::shared_ptr<std::thread>> kill_turtle_threads_;
};


#endif
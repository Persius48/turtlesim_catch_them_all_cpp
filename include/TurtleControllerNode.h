#ifndef TURTLECONTROLLERNODE_H
#define TURTLECONTROLLERNODE_H

#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "my_robot_interfaces/msg/turtle.hpp"
#include "my_robot_interfaces/msg/turtle_array.hpp"
#include "my_robot_interfaces/srv/catch_turtle.hpp"

class TurtleControllerNode : public rclcpp::Node
{
public:
    TurtleControllerNode();

private:
    void callbackPose(const turtlesim::msg::Pose::SharedPtr pose);


    double getDistanceFromCurrentPose(my_robot_interfaces::msg::Turtle turtle);

    void callbackTurtlesToCatch(const my_robot_interfaces::msg::TurtleArray::SharedPtr msg);

    void publishCmdVel(double x, double theta);

    void controlLoop();

    void callCatchTurtleService(std::string turtle_name);

    std::string name_;
    turtlesim::msg::Pose pose_;
    bool turtlesim_up_;
    bool catch_closest_turtle_first_;
    my_robot_interfaces::msg::Turtle turtle_to_catch_;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber_;
    rclcpp::Subscription<my_robot_interfaces::msg::TurtleArray>::SharedPtr turtles_to_catch_subscriber_;
    rclcpp::TimerBase::SharedPtr control_loop_timer_;

    std::vector<std::shared_ptr<std::thread>> catch_turtle_threads;
};

#endif
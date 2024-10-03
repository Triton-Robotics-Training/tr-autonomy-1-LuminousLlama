#include "spin_slow_update.h"
using std::placeholders::_1;

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SlowSolution>());
  rclcpp::shutdown();
  return 0;
}


SlowSolution::SlowSolution() : Node("slowsolution")
{
  // RCLCPP_INFO(this->get_logger(), "Remove this statement from spin_slow_update.cpp");
  mpSubscription_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "measuredpos",
      10,
      std::bind(&SlowSolution::topic_callback, this, _1));

  ppPublisher_ = this->create_publisher<ArrayMsg>("predictedpos", 10);
}

void SlowSolution::topic_callback(const ArrayMsg::SharedPtr msg){
  RCLCPP_INFO(this->get_logger(), "received: %f, %f", msg->data[0], msg->data[1]);
  ppPublisher_->publish(*msg);
}

// your code here
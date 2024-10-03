#ifndef YOUR_SOLUTION_SRC_SPIN_SOL_H_
#define YOUR_SOLUTION_SRC_SPIN_SOL_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;

class SpinSolution : public rclcpp::Node {
 public:
  SpinSolution();
 private:
  std::array<double, 2> currentPose_;
  std::array<double, 2> currentVel_;
  std::chrono::time_point<std::chrono::system_clock> lastTime_;

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<ArrayMsg>::SharedPtr ppPublisher_;
  rclcpp::Subscription<ArrayMsg>::SharedPtr mpSubscription_;
  rclcpp::Subscription<ArrayMsg>::SharedPtr mvSubscription_;


  void mpCallback(const ArrayMsg::SharedPtr msg);
  void mvCallback(const ArrayMsg::SharedPtr msg);
  void calculateAndPublishPose();
    // your code here
};

#endif //YOUR_SOLUTION_SRC_SPIN_SOL_H_

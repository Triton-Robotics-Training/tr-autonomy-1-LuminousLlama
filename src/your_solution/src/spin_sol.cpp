#include "spin_sol.h"
using std::placeholders::_1;

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SpinSolution>());
  rclcpp::shutdown();
  return 0;
}

// your code here
SpinSolution::SpinSolution() : Node("spinsolution")
{
 
   mpSubscription_ = this->create_subscription<ArrayMsg>("measuredpos",
                                                        10,
                                                        std::bind(&SpinSolution::mpCallback, this, _1));

  mvSubscription_ = this->create_subscription<ArrayMsg>("measuredvel",
                                                        10,
                                                        std::bind(&SpinSolution::mvCallback, this, _1));

  ppPublisher_ = this->create_publisher<ArrayMsg>("predictedpos", 10);

  timer_ = this->create_wall_timer(std::chrono::milliseconds(5),
                                   std::bind(&SpinSolution::calculateAndPublishPose, this));


  currentPose_ = {0,0};
  currentVel_ = {0,0};
  // your code here
}

void SpinSolution::mpCallback(const ArrayMsg::SharedPtr msg)
{
  lastTime_ = std::chrono::system_clock::now();
  currentPose_[0] = msg->data[0];
  currentPose_[1] = msg->data[1];
}

void SpinSolution::mvCallback(const ArrayMsg::SharedPtr msg)
{
  currentVel_[0] = msg->data[0];
  currentVel_[1] = msg->data[1];
}

void SpinSolution::calculateAndPublishPose()
{
  ArrayMsg::SharedPtr msg = std::make_shared<ArrayMsg>();

  auto now = std::chrono::system_clock::now();
  std::chrono::duration<double> timeElapsed = now - lastTime_;

  double dt = timeElapsed.count();
  msg->data.resize(2);

  
  msg->data[0] = currentPose_[0] + (dt * currentVel_[0]);
  msg->data[1] = currentPose_[1] + (dt * currentVel_[1]);

  ppPublisher_->publish(*msg);
}

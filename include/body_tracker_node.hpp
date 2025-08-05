#ifndef BODY_TRACKER_NODE_HPP
#define BODY_TRACKER_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "coco_interfaces/msg/body_points.hpp"
#include "coco_interfaces/msg/body_position.hpp"
#include "geometry_msgs/msg/point32.hpp"

class BodyTrackerNode : public rclcpp::Node {
public:
    BodyTrackerNode();

private:
    
    bool last_detection_valid;
    coco_interfaces::msg::BodyPosition last_valid_arm_msg;
    coco_interfaces::msg::BodyPoints::SharedPtr last_body_points_;
    
    bool has_body_points_{false};

    std::chrono::milliseconds publish_period_{300};  // periodo en ms
    rclcpp::TimerBase::SharedPtr publish_timer_;

    float angle_variation_threshold_{5.0f};

    float radian2Euler(float radian);
    float calculateAngleWithVertical(float shoulder_x, float shoulder_y, float elbow_x, float elbow_y);
    float calculateAngleWithVerticalZY(float shoulder_z, float shoulder_y, float elbow_z, float elbow_y);
    float calculateRelativeAngle(float shoulder_x, float shoulder_y, float elbow_x, float elbow_y, float wrist_x, float wrist_y);
    float calculateRelativeAngleZY(float shoulder_z, float shoulder_y, float elbow_z, float elbow_y, float wrist_z, float wrist_y);
    void bodyPointsCallback(const coco_interfaces::msg::BodyPoints::SharedPtr msg);
    void timerCallback();
    
    rclcpp::Subscription<coco_interfaces::msg::BodyPoints>::SharedPtr subscription_;
    rclcpp::Publisher<coco_interfaces::msg::BodyPosition>::SharedPtr publisher_;
};

#endif
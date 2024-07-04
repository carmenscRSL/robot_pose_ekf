#include "robot_pose_ekf/odom_filter.h"

RelayNode::RelayNode()
{
    // Initialize subscriber and publisher
    odomSub_ = nh_.subscribe("/state_estimator/pose_in_odom", 10, &RelayNode::odom_callback, this);
    odomPub_ = nh_.advertise<nav_msgs::Odometry>("/odom", 10);
}

void RelayNode::odom_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    // Republish the received message on topic "b"
    nav_msgs::Odometry odom_msg;
    odom_msg.child_frame_id = "base";
    odom_msg.header = msg->header;
    odom_msg.pose = msg->pose;
    odom_msg.pose.covariance = {0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 
                                0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 
                                0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 
                                0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 
                                0.0, 0.0, 0.0, 0.0, 0.0, 0.01};
    odomPub_.publish(odom_msg);
}

void RelayNode::run()
{
    ros::spin();
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "relay_node");

    RelayNode relayNode;
    relayNode.run();

    return 0;
}
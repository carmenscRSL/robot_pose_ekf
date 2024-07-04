#include "ros/ros.h"
#include "std_msgs/String.h"  // Assuming the message type is std_msgs/String. Change if needed.
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"

class RelayNode
{
public:
    RelayNode();
    void run();

private:
    void odom_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);

    ros::NodeHandle nh_;
    ros::Subscriber odomSub_;
    ros::Publisher odomPub_;
};

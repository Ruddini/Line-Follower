#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/CompressedImage.h>

 
#include<sensor_msgs/image_encodings.h>
#include<sensor_msgs/Image.h>
#include<sensor_msgs/CompressedImage.h>
#include<sensor_msgs/CameraInfo.h>

#define SMILE 4
#define ARROW_LEFT 3
#define ARROW_UP 5
#define ARROW_DOWN 6

int id = 0;
ros::Publisher action_pub;
geometry_msgs::Twist set_vel;

void imageCallback(const sensor_msgs::CompressedImageConstPtr& image_msg)
{

   if (id>0)
   {
      

      switch (id)
      {
      case ARROW_LEFT:
         set_vel.linear.x = 0;
         set_vel.angular.z = 1;
         break;
      case ARROW_UP:
         set_vel.linear.x = 1;
         set_vel.angular.z = 0;
         break;
      case ARROW_DOWN:
         set_vel.linear.x = -1;
         set_vel.angular.z = 0;
         break;
      default: // other object
         set_vel.linear.x = 0;
         set_vel.angular.z = 0;
      }
      action_pub.publish(set_vel);
   }
   else
   {
      // No object detected
      set_vel.linear.x = 0;
      set_vel.angular.z = 0;
      action_pub.publish(set_vel);
   }
}

int main(int argc, char **argv)
{

   ros::init(argc, argv, "action_controller");
   ros::NodeHandle n("~");
   ros::Rate loop_rate(50);
   ros::Subscriber sub = n.subscribe("/camera/rgb/image_raw/compressed", 1, imageCallback);
   action_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
   set_vel.linear.x = 0;
   set_vel.linear.y = 0;
   set_vel.linear.z = 0;
   set_vel.angular.x = 0;
   set_vel.angular.y = 0;
   set_vel.angular.z = 0;
   while (ros::ok())
   {
      ros::spinOnce();
      loop_rate.sleep();
   }
}

#!/usr/bin/env python2
import rospy 
from sensor_msgs.msg import Image
from cv_bridge import CvBridge 
import cv2
import line_detection
##============================================================
from std_msgs.msg import String


##============================================================
def callback(data):
	br= CvBridge()
	rospy.loginfo("receiving video frame")
	current_frame = br.imgmsg_to_cv2(data)
## current_frame to nasza klatka obrazu 
	cv2.imshow("camera",current_frame)
# ============
	a = line_detection.LineDetector(vc = current_frame)
	e = a.detection_color_line()
	cv2.imshow("Przetworzony obraz",e)
# ============	
	cv2.waitKey(1)


def talker ():
	pub = rospy.Publisher("/teleop_twist_keyboard", String, queue_size=100)
	
	rospy.loginfo("sending message")
	pub.publish(ord('u'))

def receive_message():
	rospy.init_node("vid_sub",anonymous = True)
#==========
# Talker nie dziala zbyt dobrze ale nie sypie bledami
	rate = rospy.Rate(10)
	#alker()
#==========
	rospy.Subscriber("/camera/rgb/image_raw", Image, callback)
	rospy.spin()

if __name__ == "__main__":
	receive_message()

#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
import sys

def turtle_circle():
    rospy.init_node('turtlesim', anonymous=True)
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    rate = rospy.Rate(1)
    vel = Twist()
    i = 0
    width = 4 
    height = 2
    while not rospy.is_shutdown():
        if i % 2 == 0:
            vel.linear.x = width
            vel.linear.y = 0
            vel.linear.z = 0
            vel.angular.x = 0
            vel.angular.y = 0
            vel.angular.z = 0
            pub.publish(vel)
            rate.sleep()
            width = -width
            i += 1
        else:
            vel.linear.x = 0
            vel.linear.y = height
            vel.linear.z = 0
            vel.angular.x = 0
            vel.angular.y = 0
            vel.angular.z = 0
            pub.publish(vel)
            rate.sleep()
            height = -height
            i += 1


if __name__ == '__main__':
	try:
		turtle_circle()
	except rospy.ROSInterruptException:
		pass


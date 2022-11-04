#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

#define echoPin 6
#define trigPin 7

long duration;
float distance;

ros::NodeHandle nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range("/ultrasonic_range", &range_msg);
char frameid[]= "/ultrasound";

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode ( echoPin, INPUT);

  nh.initNode();
  nh.advertise(pub_range);

  range_msg.radiation_type= sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id = frameid;
  range_msg.field_of_view =0.01;
  range_msg.min_range = 0.03;
  range_msg.max_range = 3.0;

}

void loop() {
  // put your main code here, to run repeatedly:
  range_msg.range = getRange();
  range_msg.header.stamp = nh.now();
  pub_range.publish (&range_msg);
  nh.spinOnce();
  delay (100);


}

float getRange(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds (2);
  digitalWrite (trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite (echoPin, LOW);

  duration = pulseIn(echoPin,HIGH);
  distance = duration * 0.000343/2;
  
  return distance;
  
}

/*
    tf2_human_broadcaster node

    Copyright 2022 Università degli studi della Campania "Luigi Vanvitelli"
    Author: Marco Costanzo <marco.costanzo@unicampania.it>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <geometry_msgs/TransformStamped.h>
#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "tf2_human_broadcaster");

  ros::NodeHandle node;
  ros::NodeHandle node_private("~");

  std::string base_link;
  node_private.param("base_link", base_link, std::string("base_link"));

  static tf2_ros::TransformBroadcaster br;

  ros::Rate loop_rate(10);
  ros::Time t0 = ros::Time::now();
  ros::Duration t(0.0);

  while (ros::ok()) {

    loop_rate.sleep();
    ros::spinOnce();

    t = ros::Time::now() - t0;

    geometry_msgs::TransformStamped transformStamped;

    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = base_link;

    transformStamped.child_frame_id = "human";

    transformStamped.transform.translation.x =
        0.5*(0.8+0.25) + 0.5*(0.8-0.25) * sin(2.0 * M_PI * 0.05 * t.toSec());
    transformStamped.transform.translation.y = 0.0;
    transformStamped.transform.translation.z = 0.25;

    transformStamped.transform.rotation.x = 0.0;
    transformStamped.transform.rotation.y = 0.0;
    transformStamped.transform.rotation.z = 0.0;
    transformStamped.transform.rotation.w = 1.0;

    br.sendTransform(transformStamped);
  }

  return 0;
};
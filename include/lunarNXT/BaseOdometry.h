//=============================================================================
//
// This file is part of LunarNXT.
//
// LunarNXT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// LunarNXT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LunarNXT. If not, see <http://www.gnu.org/licenses/>.
//
//=============================================================================

#ifndef BASEODOMETRY_H
#define BASEODOMETRY_H

#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "kdl/frames.hpp"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Odometry.h"
#include "nxt_msgs/Range.h"
#include "nxt_msgs/JointCommand.h"
#include "tf_conversions/tf_kdl.h"

#define PUBLISH_TF true

namespace Lunar_lib {

/**
 * @deprecated Classe inutilisee
 */
class BaseOdometry {
private:
	std::vector<float> leftPosition;
	std::vector<float> rightPosition;
	
	float rot_covar;
	
	bool initialized;
	KDL::Frame pose;
	
	tf::TransformBroadcaster br;

	ros::NodeHandle n;
	ros::Publisher publisher;
public:
	BaseOdometry();
	nav_msgs::Odometry update(sensor_msgs::JointState msg);
};

};

#endif

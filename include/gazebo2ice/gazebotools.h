/*
 *  Copyright (C) 1997-2015 JDE Developers Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see http://www.gnu.org/licenses/.
 *  Authors :
 *       Victor Arribas Raigadas <.varribas.urjc@gmail.com>
 */


#ifndef GAZEBO2ICE_GAZEBOTOOLS_H
#define GAZEBO2ICE_GAZEBOTOOLS_H

#include <gazebo/gazebo.hh>
#include <gazebo/physics/Model.hh>
#include <gazebo/physics/Link.hh>
#include <gazebo/sensors/Sensor.hh>

namespace gazebo2ice {

std::vector<int> getLinksIds(gazebo::physics::ModelPtr model);

bool isMemberOf(int, std::vector<int>);
bool isMemberOf(gazebo::sensors::SensorPtr, std::vector<int>);
bool isMemberOf(gazebo::sensors::SensorPtr, gazebo::physics::ModelPtr);

}//NS

#endif // GAZEBO2ICE_GAZEBOTOOLS_H

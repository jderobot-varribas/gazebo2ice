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

#ifndef GAZEBO2ICE_ICEMODELPLUGIN_H
#define GAZEBO2ICE_ICEMODELPLUGIN_H

#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/common/Exception.hh>

#include "gazebo2ice/globalicemanager.h"


namespace gazebo2ice{

class IceModelPlugin : public gazebo::ModelPlugin
{
public:
    IceModelPlugin();
    virtual ~IceModelPlugin();
    std::string _log_prefix;

/// Gazebo
protected:
    void Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf);
    void Init();
    void OnSigInt();

private:
    gazebo::physics::ModelPtr model;
    gazebo::event::ConnectionPtr sigintConnection;

};

}//NS

#endif // GAZEBO2ICE_ICEMODELPLUGIN_H

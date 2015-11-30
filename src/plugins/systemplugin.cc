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


#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/common/Exception.hh>

#include "gazebo2ice/globalicemanager.h"


namespace gazebo2ice{

class IceLoadArgsPlugin : public gazebo::SystemPlugin{
public:
    IceLoadArgsPlugin(){}

public:
    void Load(int argc, char** argv){
        GlobalIceManager::externalBootstrap(Ice::initialize(argc, argv));
        std::cout<<"Ice initialized with argc argv"<<std::endl;

        sigintConnection = gazebo::event::Events::ConnectSigInt(
                    boost::bind(&IceLoadArgsPlugin::OnSigInt,this));
    }
    void Init() {}
    void Reset() {}

    void OnSigInt(){
        std::cout<<"IceLoadArgsPlugin::OnSigInt()"<<std::endl;
        GlobalIceManager::getInstance()->ic->shutdown();
    }

private:
    gazebo::event::ConnectionPtr sigintConnection;

};

}//NS

GZ_REGISTER_SYSTEM_PLUGIN(gazebo2ice::IceLoadArgsPlugin)

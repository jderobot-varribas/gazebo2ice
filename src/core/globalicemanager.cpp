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

#include "gazebo2ice/globalicemanager.h"


using namespace gazebo2ice;

IceManagerPtr GlobalIceManager::Instance;

IceManagerPtr
GlobalIceManager::getInstance(){
    if (!Instance)
        internalBootstrap();
    return Instance;
}

void
GlobalIceManager::internalBootstrap(){
    Instance = IceManagerPtr(new IceManager(Ice::initialize()));
}

void
GlobalIceManager::externalBootstrap(Ice::CommunicatorPtr ic){
    if (Instance)
        throw gazebo::common::Exception("globalicemanager.cpp", 43, "externalBootstrap is only allowed if Instance is NULL");
    Instance = IceManagerPtr(new IceManager(ic));;
}
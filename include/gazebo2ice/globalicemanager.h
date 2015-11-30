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

#ifndef GAZEBO2ICE_GLOBALICEMANAGER_H
#define GAZEBO2ICE_GLOBALICEMANAGER_H

#include "gazebo2ice/icemanager.h"
#include <gazebo/common/Exception.hh>

namespace gazebo2ice {

//// Singleton (thread unsafe)
class GlobalIceManager
{
private:
    GlobalIceManager(){}

public:
    static IceManagerPtr getInstance();

    static void internalBootstrap();
    static void externalBootstrap(Ice::CommunicatorPtr);

private:
    static IceManagerPtr Instance;
};


}//NS

#endif // GAZEBO2ICE_GLOBALICEMANAGER_H

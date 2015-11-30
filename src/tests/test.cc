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

#include <iostream>
#include <gazebo2ice/globalicemanager.h>
#include <jderobot/pose3d.h>

using namespace gazebo2ice;


int main(){

    IceManagerPtr im = GlobalIceManager::getInstance();
    Ice::ObjectAdapterPtr adapter = im->findIceAdapterForId(0);
    std::cout << "Adapter: " << adapter.get() << std::endl;


    Ice::ObjectAdapterPtr adapter2 = im->ic->createObjectAdapterWithEndpoints("Ejemplo", "default -h localhost -p 9850");

    std::vector<int> ids; ids.push_back(1);
    im->registerAdapter(adapter2, ids);


    adapter = im->findIceAdapterForId(1);
    std::cout << "Adapter: " << adapter.get() << std::endl;

    im->ic->shutdown();
    im->ic->waitForShutdown();
    return 0;
}

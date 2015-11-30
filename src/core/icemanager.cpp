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

#include "gazebo2ice/icemanager.h"

using namespace gazebo2ice;

IceManager::IceManager(Ice::CommunicatorPtr ic):
    ic(ic)
{}

IceManager::~IceManager(){
    if (ic){
        if (!ic->isShutdown()){
            std::cout<<"[IceManager destructor] shuting down Ice (communicator "<<ic.get()<<")"<<std::endl;
            ic->shutdown();
            ic->waitForShutdown();
        }else{
            std::cout<<"[IceManager destructor] nothing to do."<<std::endl;
        }
    }
}


void
IceManager::registerAdapter(Ice::ObjectAdapterPtr adapter, std::vector<int> ids){
    modelAdapters.push_back(ModelAdapterPair(adapter, ids));
}

void
IceManager::registerAdapter(Ice::ObjectAdapterPtr adapter, gazebo::physics::ModelPtr model){
    registerAdapter(adapter, getLinksIds(model));
}

Ice::ObjectAdapterPtr
IceManager::findIceAdapterForId(int id){
    for (ModelAdapterPair entry : modelAdapters){
        if (isMemberOf(id, entry.ids))
            return entry.adapter;
    }

    return 0;
}

Ice::ObjectAdapterPtr
IceManager::findIceAdapterForModel(gazebo::physics::ModelPtr m){
    int id = m->GetLink()->GetId();
    return findIceAdapterForId(id);
}

Ice::ObjectAdapterPtr
IceManager::findIceAdapterForSensor(gazebo::sensors::SensorPtr s){
    int id = s->GetParentId();
    return findIceAdapterForId(id);
}


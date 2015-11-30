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

#ifndef GAZEBO2ICE_ICEMANAGER_H
#define GAZEBO2ICE_ICEMANAGER_H


#include <boost/shared_ptr.hpp>
#include <Ice/Ice.h>

#include "gazebo2ice/gazebotools.h"

namespace gazebo2ice {


typedef struct modeladapterpair{
    Ice::ObjectAdapterPtr adapter;
    std::vector<int> ids;

    modeladapterpair(Ice::ObjectAdapterPtr adapter, std::vector<int> ids):adapter(adapter),ids(ids){}
} ModelAdapterPair;

typedef std::pair<int, Ice::ObjectAdapterPtr> Entry;


class IceManager
{
public:
    IceManager(Ice::CommunicatorPtr);
    virtual ~IceManager();

    void registerAdapter(Ice::ObjectAdapterPtr, std::vector<int>);
    void registerAdapter(Ice::ObjectAdapterPtr, gazebo::physics::ModelPtr);

    Ice::ObjectAdapterPtr findIceAdapterForId(int);
    Ice::ObjectAdapterPtr findIceAdapterForModel(gazebo::physics::ModelPtr);
    Ice::ObjectAdapterPtr findIceAdapterForSensor(gazebo::sensors::SensorPtr);

public:
    const Ice::CommunicatorPtr ic;

private:
    std::list< ModelAdapterPair > modelAdapters;
    std::map<int,Ice::ObjectAdapterPtr> indexedAdapters;

};

typedef boost::shared_ptr<IceManager> IceManagerPtr;

}//NS

#endif // GAZEBO2ICE_ICEMANAGER_H

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

#include "gazebo2ice/gazebotools.h"

namespace gazebo2ice {


std::vector<int>
getLinksIds(gazebo::physics::ModelPtr model){
    std::vector<gazebo::physics::LinkPtr> links = model->GetLinks();
    int size = links.size();
    std::vector<int> ids(size);
    for (int i=0; i<size; i++){
        ids[i] = links[i]->GetId();
    }

    return ids;
}


bool
isMemberOf(int id, std::vector<int> ids){
    return ids.end() != std::find(ids.begin(), ids.end(), id);
}

bool
isMemberOf(gazebo::sensors::SensorPtr s, std::vector<int> ids){
    int id = s->GetParentId();
    return isMemberOf(id, ids);
}


bool
isMemberOf(gazebo::sensors::SensorPtr s, gazebo::physics::ModelPtr m){
    return isMemberOf(s, getLinksIds(m));
}


}//NS

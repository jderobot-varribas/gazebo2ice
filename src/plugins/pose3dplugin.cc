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



#include <gazebo2ice/globalicemanager.h>
#include <jderobot/pose3d.h>

namespace gazebo2ice {

jderobot::Pose3DDataPtr
gazeboPose3DToMsg (gazebo::math::Pose pose){
    jderobot::Pose3DDataPtr data(new jderobot::Pose3DData());

    data->x = pose.pos.x;
    data->y = pose.pos.y;
    data->z = pose.pos.z;
    data->h = 1;
    data->q0 = pose.rot.w;
    data->q1 = pose.rot.x;
    data->q2 = pose.rot.y;
    data->q3 = pose.rot.z;

    return data;
}


class PushPose3DI : public jderobot::Pose3D {
private:
    jderobot::Pose3DDataPtr data;

public:
    void pushData(jderobot::Pose3DDataPtr _data){
        data->x = _data->x;
        data->y = _data->y;
        data->z = _data->z;
        data->h = _data->h;
        data->q0 = _data->q0;
        data->q1 = _data->q1;
        data->q2 = _data->q2;
        data->q3 = _data->q3;
    }

    PushPose3DI ():
        data(new jderobot::Pose3DData(0,0,0,0,0,0,0,0))
    {}

    ~PushPose3DI ()
    {}

    jderobot::Pose3DDataPtr
    getPose3DData ( const Ice::Current& ){
        return data;
    }

    Ice::Int
    setPose3DData ( const jderobot::Pose3DDataPtr & /*data*/, const Ice::Current& ){
        return 0;
    }
};


class Pose3DPlugin : public gazebo::ModelPlugin {
public:
    Pose3DPlugin(){}

    ~Pose3DPlugin(){
        gazebo::event::Events::DisconnectWorldUpdateBegin(sub);
    }

/// Gazebo
protected:
    void Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr /*_sdf*/){
        model = _model;

        IceManagerPtr im = GlobalIceManager::getInstance();
        Ice::ObjectAdapterPtr adapter = im->findIceAdapterForModel(_model);
        //std::string name = im->ic->getProperties()->getProperty("Name");
        Ice::ObjectPtr pose3di = iceInterface = new PushPose3DI();
        adapter->add(pose3di, im->ic->stringToIdentity("Pose3D"));
    }

    void Init(){
        sub = gazebo::event::Events::ConnectWorldUpdateBegin(
            boost::bind(&Pose3DPlugin::OnUpdate, this));
    }

    void OnUpdate(){
        gazebo::math::Pose pose = model->GetWorldPose();
        jderobot::Pose3DDataPtr data = gazeboPose3DToMsg(pose);
        iceInterface->pushData(data);
    }

private:
    PushPose3DI* iceInterface;
    gazebo::physics::ModelPtr model;
    gazebo::event::ConnectionPtr sub;
};

}//NS

GZ_REGISTER_MODEL_PLUGIN(gazebo2ice::Pose3DPlugin)


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


#include "gazebo2ice/icemodelplugin.hh"

GZ_REGISTER_MODEL_PLUGIN(gazebo2ice::IceModelPlugin)

using namespace gazebo2ice;
using namespace gazebo::physics;
using namespace gazebo::event;

IceModelPlugin::IceModelPlugin()
{}

IceModelPlugin::~IceModelPlugin(){
}


void
IceModelPlugin::Load(ModelPtr _model, sdf::ElementPtr _sdf){
    model = _model;
    _log_prefix = "["+_model->GetName()+"] ";

    std::cout << _log_prefix <<"creating Ice Adapter"<<std::endl;
    if(!_sdf->HasElement("iceConfigFile"))
        throw gazebo::common::Exception("icemodelplugin.cc", 40, "Model must have an 'iceConfigFile' entry.");
    if(!_sdf->HasElement("iceConfigPrefix"))
        throw gazebo::common::Exception("icemodelplugin.cc", 42, "Model must have an 'iceConfigPrefix' entry.");

    std::string iceConfigFile =  _sdf->GetElement("iceConfigFile")->GetValue()->GetAsString();
    std::string iceConfigPrefix =  _sdf->GetElement("iceConfigPrefix")->GetValue()->GetAsString();
    if (!iceConfigPrefix.empty()) iceConfigPrefix += ".";

    IceManagerPtr im = GlobalIceManager::getInstance();
    im->ic->getProperties()->load(iceConfigFile);
    Ice::ObjectAdapterPtr adapter = im->ic->createObjectAdapter(iceConfigPrefix+"Adapter");
    std::cout<<_log_prefix<<"Created adapter "<< adapter.get() <<std::endl;

    im->registerAdapter(adapter, model);

    sigintConnection = Events::ConnectSigInt(
        boost::bind(&IceModelPlugin::OnSigInt, this));
}


void
IceModelPlugin::Init(){
    IceManagerPtr im = GlobalIceManager::getInstance();
    Ice::ObjectAdapterPtr adapter = im->findIceAdapterForModel(model);
    adapter->activate();
}

void
IceModelPlugin::OnSigInt(){
    std::cout <<_log_prefix<<"shuting down Ice Adapter..."<<std::endl;
    Ice::ObjectAdapterPtr adapter = GlobalIceManager::getInstance()->findIceAdapterForModel(model);
    adapter->deactivate();
    GlobalIceManager::getInstance()->ic->shutdown();
}

/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolume.cpp
@author Cedric ROMAN - roman@numengo.com
@date February 2009
@brief File containing NgoGeoVolume class definition
*/
/*******************************************************************************
   LICENSE
*******************************************************************************
 Copyright (C) 2009 Numengo (admin@numengo.com)

 This document is released under the terms of the numenGo EULA.  You should have received a
 copy of the numenGo EULA along with this file; see  the file LICENSE.TXT. If not, write at
 admin@numengo.com or at NUMENGO, 15 boulevard Vivier Merle, 69003 LYON - FRANCE
 You are not allowed to use, copy, modify or distribute this file unless you  conform to numenGo
 EULA license.
*/


/*******************************************************************************
   REVISIONS
*******************************************************************************/

/*******************************************************************************
   INCLUDES
*******************************************************************************/

#include "ngogeo/NgoGeoVolume.h"

/*******************************************************************************
   CLASS NgoGeoVolumeManager DEFINITION
*******************************************************************************/

//DESCRIPTION_MANAGER(NgoGeoVolumeManager,"NgoGeoVolume","Constructor(NgoObj::NgoComponent &)");
//template<> NgoGeoVolumeManager * NgoSingleton<NgoGeoVolumeManager >::instance_ = 0L;
//template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoVolume, CreateVolume>::name = "NgoGeoVolumeManager";
//template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoVolume, CreateVolume>::type = "NgoGeo::NgoGeoVolume";
//template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoVolume, CreateVolume>::description = "Constructor(NgoObj::NgoComponent &)";
template<> NgoGeoVolumeManager * NgoSingleton< NgoGeoVolumeManager >::instance_ = 0L;
template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoVolume, CreateVolume>::name = "NgoGeoVolumeManager";
template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoVolume, CreateVolume>::type = "NgoGeo::NgoGeoVolume";
template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoVolume, CreateVolume>::description = "Constructor(NgoObj::NgoComponent &)";

NgoGeo::NgoGeoVolume * NgoGeoVolumeManager::create(NgoObj::NgoComponent & geometry, const char * label)
{
   std::string i_name;
   if (label)
      i_name = label;
   else
   {
      if (geometry.hasXsiType())
         i_name = geometry.getXsiType();
      else if (geometry.hasName())
         i_name = geometry.getName();
   }

   if (hasObjectWithName(i_name.c_str()))
      return findByName(i_name.c_str()).back()->Constructor(geometry);
   if (hasObjectWithXsiType(i_name.c_str()))
      return findByXsiType(i_name.c_str()).back()->Constructor(geometry);

   return (NgoGeo::NgoGeoVolume*)0L;
}

namespace NgoGeo {

/*******************************************************************************
   CLASS NgoGeoSurfaceManager DEFINITION
*******************************************************************************/
static std::vector<NgoGeoVolume *> volumes_;
std::vector<NgoGeo::NgoGeoVolume *> & getVolumes() { return volumes_;};
NgoGeo::NgoGeoVolume * getVolume(const int index)
{
    if (index==-1)
        throw NgoErrorInvalidArgument(1,"trying to access a surface which has not been properly initialized","NgoGeo","NgoGeo::getVolume");
    if (index>=volumes_.size())
        throw NgoErrorInvalidArgument(1,"invalid accessor (> size)","NgoGeo","NgoGeo::getVolume");
    return volumes_[index];
};
NgoGeo::NgoGeoVolume * getVolume(const variableInteger & index)
{
    return getVolume(index());
};

/*******************************************************************************
   CLASS NgoGeoVolume DEFINITION
*******************************************************************************/
IMPLEMENT_ABSTRACT_CLASS_NGO(NgoGeoVolume,NgoObject)

NgoGeoVolume::NgoGeoVolume()
:NgoGeoGeometry()
{
    doCreate();
    NgoGeoVolumeManager::get()->onConstruction(this);
    volumeIndex = volumes_.size();
    volumes_.push_back(this);
}

void NgoGeoVolume::doCreate()
{
    setInstanceName("NgoGeoVolume");
    // add an index of surface and initialize it
    registerVariableWithReference(vr_NgoGeoVolume_surface    ,surface    );
    registerVariableWithReference(vr_NgoGeoVolume_volume     ,volume     );
    registerVariableWithReference(vr_NgoGeoVolume_volumeIndex,volumeIndex);

    associateMethodToVariable1(surface,NgoGeoVolume,doCalcSurface,mainModule);
    associateMethodToVariable1(volume,NgoGeoVolume,doCalcVolume,mainModule);

    registerPort(portVolume);
    portVolume.addVariable(volumeIndex);
};

NgoGeoVolume::~NgoGeoVolume()
{
   NgoGeoVolumeManager::get()->onDestruction(this);
}

NgoGeoVolume::NgoGeoVolume(const NgoGeoVolume & rhs)
:NgoGeoGeometry(rhs)
{
    doCreate();
    *this = rhs;
    NgoGeoVolumeManager::get()->onConstruction(this);
    volumeIndex = volumes_.size();
    volumes_.push_back(this);
}

NgoGeoVolume & NgoGeoVolume::operator=(const NgoGeoVolume & rhs)
{
    if (this != &rhs)
    {
        NgoGeoGeometry::operator=(rhs);
        surface          = rhs.surface          ;
        volume           = rhs.volume           ;
    }
    return *this;
}


} // namespace NgoGeo

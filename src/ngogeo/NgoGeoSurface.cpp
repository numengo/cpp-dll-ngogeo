/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurface.cpp
@author Cedric ROMAN - roman@numengo.com
@date February 2009
@brief File containing NgoGeoSurface class definition
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

#include "ngogeo/NgoGeoSurface.h"

//DESCRIPTION_MANAGER(NgoGeoSurfaceManager,"NgoGeoSurface","Constructor(NgoObj::NgoComponent &)");
//template<> NgoObjectManagerBase<NgoGeo::NgoGeoSurface, CreateSurface> * NgoSingleton<NgoObjectManagerBase<NgoGeo::NgoGeoSurface, CreateSurface> >::instance_ = 0L;
//template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoSurface, CreateSurface>::name = "NgoGeoSurfaceManager";
//template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoSurface, CreateSurface>::type = "NgoGeo::NgoGeoSurface";
//template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoSurface, CreateSurface>::description = "Constructor(NgoObj::NgoComponent &)";

template<> NgoGeoSurfaceManager * NgoSingleton< NgoGeoSurfaceManager >::instance_ = 0L;
template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoSurface, CreateSurface>::name = "NgoGeoSurfaceManager";
template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoSurface, CreateSurface>::type = "NgoGeo::NgoGeoSurface";
template<> std::string NgoObjectManagerBase<NgoGeo::NgoGeoSurface, CreateSurface>::description = "Constructor(NgoObj::NgoComponent &)";

NgoGeo::NgoGeoSurface * NgoGeoSurfaceManager::create(NgoObj::NgoComponent & component, const char * label)
{
   std::string i_name;
   if (label)
      i_name = label;
   else
   {
      if (component.hasXsiType())
         i_name = component.getXsiType();
      else if (component.hasName())
         i_name = component.getName();
   }

   if (NgoGeoSurfaceManager::hasObjectWithName(i_name.c_str()))
      return findByName(i_name.c_str()).back()->Constructor(component);
   if (NgoGeoSurfaceManager::hasObjectWithXsiType(i_name.c_str()))
      return findByXsiType(i_name.c_str()).back()->Constructor(component);

   return (NgoGeo::NgoGeoSurface*)0L;
}


namespace NgoGeo {

/*******************************************************************************
   CLASS NgoGeoSurfaceManager DEFINITION
*******************************************************************************/
static std::vector<NgoGeoSurface *> surfaces_;
std::vector<NgoGeo::NgoGeoSurface *> & getSurfaces() { return surfaces_;};
NgoGeo::NgoGeoSurface * getSurface(const int index)
{
    if (index==-1)
        throw NgoErrorInvalidArgument(1,"trying to access a surface which has not been properly initialized","NgoGeo","NgoGeo::getSurface");
    if (index>=surfaces_.size())
        throw NgoErrorInvalidArgument(1,"invalid accessor (> size)","NgoGeo","NgoGeo::getSurface");
    return surfaces_[index];
};
NgoGeo::NgoGeoSurface * getSurface(const variableInteger & index)
{
    return getSurface(index());
};

/*******************************************************************************
   CLASS NgoGeoSurface DEFINITION
*******************************************************************************/

IMPLEMENT_ABSTRACT_CLASS_NGO(NgoGeoSurface,NgoGeoGeometry)

NgoGeoSurface::NgoGeoSurface()
:NgoGeoGeometry(),isHydDiamUserDef(false)
{
    NgoGeoSurfaceManager::get()->onConstruction(this);
    surfaceIndex = surfaces_.size();
    surfaces_.push_back(this);
    doCreate();
}

/*! @brief method to compute surface */
double NgoGeoSurface::computeSurface() {
    surface.update();
    return surface();
 };

double NgoGeoSurface::computePerimeter() {
    perimeter.update();
    return perimeter();
};

double NgoGeoSurface::computeHydraulicDiameter()
{
    hydraulicDiameter.update();
    return hydraulicDiameter();
};

void NgoGeoSurface::setHydraulicDiameter(double diam)
{
   hydraulicDiameter = diam;
   isHydDiamUserDef = true;
};

void NgoGeoSurface::doCalcHydraulicDiameter()
{
    if (isHydDiamUserDef()) {
        hydraulicDiameter = sqrt(fabs(mainModule() )) * hydraulicDiameter() * hydraulicDiameter.module();
    }
    else 
    {
        surface.update();
        perimeter.update();
        hydraulicDiameter = 4. * surface() / perimeter();
    }
};

void NgoGeoSurface::doCreate()
{
    setInstanceName("NgoGeoSurface");
    // add an index of surface and initialize it
    registerVariableWithReference(vr_NgoGeoSurface_surface          ,surface          );
    registerVariableWithReference(vr_NgoGeoSurface_perimeter        ,perimeter        );
    registerVariableWithReference(vr_NgoGeoSurface_hydraulicDiameter,hydraulicDiameter);
    registerVariableWithReference(vr_NgoGeoSurface_surfaceIndex     ,surfaceIndex     );

    associateMethodToVariable2(hydraulicDiameter,NgoGeoSurface,doCalcHydraulicDiameter,surface,perimeter);
    associateMethodToVariable1(surface,NgoGeoSurface,doCalcSurface,mainModule);
    associateMethodToVariable1(perimeter,NgoGeoSurface,doCalcPerimeter,mainModule);

    registerPort(portSurface);
    portSurface.addVariable(surfaceIndex);
}

NgoGeoSurface::~NgoGeoSurface()
{
   surfaces_[surfaceIndex()] = 0L;
   NgoGeoSurfaceManager::get()->onDestruction(this);
}

NgoGeoSurface::NgoGeoSurface(const NgoGeoSurface & rhs)
:NgoGeoGeometry(rhs)
{
    *this = rhs;
    NgoGeoSurfaceManager::get()->onConstruction(this);
    surfaceIndex = surfaces_.size();
    surfaces_.push_back(this);
    doCreate();
}

NgoGeoSurface & NgoGeoSurface::operator=(const NgoGeoSurface & rhs)
{
    if (this != &rhs)
    {
        NgoGeoGeometry::operator=(rhs);
        surface          = rhs.surface          ;
        perimeter        = rhs.perimeter        ;
        hydraulicDiameter= rhs.hydraulicDiameter;
    }
    return *this;
}

} // namespace NgoGeo

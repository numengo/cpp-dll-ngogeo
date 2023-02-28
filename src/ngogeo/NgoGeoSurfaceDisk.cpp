/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceDisk.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoSurfaceDiskDef "Geometry".
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
   DOXYGEN GROUP DEFINION
*******************************************************************************/


/*******************************************************************************
   INCLUDES
*******************************************************************************/
#include <math.h>
#include <iostream>
#include <sstream>

#include "ngoobj/NgoVariable.h"

#include "ngogeo/NgoGeoSurfaceDisk.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_SURFACE(NgoGeo::NgoGeoSurfaceDisk,"Description of a surface disk","NgoGeoSurfaceDiskType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoSurfaceDisk DEFINITION
*******************************************************************************/
REGISTER_SURFACE(NgoGeoSurfaceDisk);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoSurfaceDisk, NgoGeoSurface)


NgoGeoSurfaceDisk::NgoGeoSurfaceDisk()
:NgoGeoSurface()
{
   NgoComponent::create();
}

NgoGeoSurfaceDisk::NgoGeoSurfaceDisk(double diameter)
:NgoGeoSurface()
{
   NgoComponent::create();
   this->diameter = diameter;
}

bool NgoGeoSurfaceDisk::create(NgoObj::NgoComponent & geometry)
{
   NgoComponent::create();
   if (geometry.hasVariableNamed("DIAMETER"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("Diameter").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      this->diameter = q();
      return true;
   }
   return false;
}

double NgoGeoSurfaceDisk::doComputeSurface()
{
    return (double) diameter.modulated() * diameter.modulated() * 0.25 * d_pi;
}

double NgoGeoSurfaceDisk::doComputePerimeter()
{
    return (double) diameter.modulated() * d_pi;
}

} // namespace NgoGeo

using namespace NgoGeo;
/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoSurfRegister(double surf)
{
   try
   {
      double diam = pow(4.*fabs(surf)/d_pi,1./2.);
      return NgoGeoSurfRegisterDisk(diam);
   }
   CATCH_GEO("NgoGeoSurfRegister")
   return -1;
}

int NgoGeoSurfRegisterDisk(double diam)
{
   try
   {
      NgoGeoSurface * surf = new NgoGeoSurfaceDisk(diam);
      if (!surf)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfRegisterDisk")
   return -1;
}

/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceRing.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoSurfaceRingDef "Geometry".
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

#include "ngogeo/NgoGeoSurfaceRing.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_SURFACE(NgoGeo::NgoGeoSurfaceRing,"Description of a annular surface","NgoGeoSurfaceRingType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoSurfaceRing DEFINITION
*******************************************************************************/
REGISTER_SURFACE(NgoGeoSurfaceRing);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoSurfaceRing, NgoGeoSurface)


NgoGeoSurfaceRing::NgoGeoSurfaceRing()
:NgoGeoSurface()
{
   NgoComponent::create();
}

NgoGeoSurfaceRing::NgoGeoSurfaceRing(double diameter1, double diameter2)
:NgoGeoSurface()
{
   NgoComponent::create();
   this->diameter1 = diameter1;
   this->diameter2 = diameter2;
}

bool NgoGeoSurfaceRing::create(NgoObj::NgoComponent & geometry)
{
   std::vector<double> params;
   if (geometry.hasVariableNamed("DIAMETER1"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("DIAMETER1").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      diameter1 = q();
       if (geometry.hasVariableNamed("DIAMETER2"))
       {
          NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("DIAMETER2").front();
          NgoQuantity q = vq->getValue();
          q.convert();
          diameter2 = q();
          return true;
       }
   }
   return false;
}



double NgoGeoSurfaceRing::doComputeSurface()
{
    return (double)
      ( (diameter1.modulated() * diameter1.modulated())
       -(diameter2.modulated() * diameter2.modulated())
      ) * 0.25 * d_pi;
}

double NgoGeoSurfaceRing::doComputePerimeter()
{
    return (double) d_pi * (diameter1.modulated() + diameter2.modulated());
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoSurfRegisterRing(double diam1, double diam2)
{
   try
   {
      if (diam2>diam1)
         throw NgoErrorInvalidArgument(2,"inner diameter should be smaller than outer diameter","","numenGo|Fl");
      NgoGeoSurface * surf = new NgoGeoSurfaceRing(diam1,diam2);
      if (!surf)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfRegisterRing")
   return -1;
}

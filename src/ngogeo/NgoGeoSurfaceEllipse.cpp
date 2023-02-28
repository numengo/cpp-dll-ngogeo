/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceEllipse.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoSurfaceEllipseDef "Geometry".
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

#include "ngogeo/NgoGeoSurfaceEllipse.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_SURFACE(NgoGeo::NgoGeoSurfaceEllipse,"Description of an elliptic surface","NgoGeoSurfaceEllipseType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoSurfaceEllipse DEFINITION
*******************************************************************************/
REGISTER_SURFACE(NgoGeoSurfaceEllipse);

IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoSurfaceEllipse, NgoGeoSurface)

NgoGeoSurfaceEllipse::NgoGeoSurfaceEllipse()
:NgoGeoSurface()
{
   NgoComponent::create();
}

NgoGeoSurfaceEllipse::NgoGeoSurfaceEllipse(double axis1, double axis2)
:NgoGeoSurface()
{
   NgoComponent::create();
   this->axis1 = axis1;
   this->axis2 = axis2;
}

bool NgoGeoSurfaceEllipse::create(NgoObj::NgoComponent & geometry)
{
   if (geometry.hasVariableNamed("AXIS1"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("Diameter").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      axis1 = q();
       if (geometry.hasVariableNamed("AXIS2"))
       {
          NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("Diameter").front();
          NgoQuantity q = vq->getValue();
          q.convert();
          axis2 = q();
          return true;
       }
   }
   return false;
}

double NgoGeoSurfaceEllipse::doComputeSurface()
{
    return (double) 0.25 * d_pi * axis1.modulated() * axis2.modulated();
}

double NgoGeoSurfaceEllipse::doComputePerimeter()
{
    //D_PI * (3. * (a+b) - sqrt((3.*a+b)*(3.*a+b)));
    double ab = axis1.modulated() * axis2.modulated();
    return (double) d_pi * (3. * ab - sqrt((3.*ab)*(3*ab)));
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoSurfRegisterEllipse(double axis1, double axis2)
{
   try
   {
      NgoGeoSurface * surf = new NgoGeoSurfaceEllipse(axis1, axis2);
      if (!surf)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfRegisterEllipse")
   return -1;
}

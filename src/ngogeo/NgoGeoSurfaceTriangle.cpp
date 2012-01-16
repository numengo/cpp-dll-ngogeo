/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceTriangle.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoSurfaceTriangleDef "Geometry".
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

#include "ngogeo/NgoGeoSurfaceTriangle.h"

#include "ngosim/NgoFmiExport.cpp"


DESCRIPTION_SURFACE(NgoGeo::NgoGeoSurfaceTriangle,"Description of a triangular surface","NgoGeoSurfaceTriangleType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoSurfaceTriangle DEFINITION
*******************************************************************************/
REGISTER_SURFACE(NgoGeoSurfaceTriangle);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoSurfaceTriangle, NgoGeoSurface)


NgoGeoSurfaceTriangle::NgoGeoSurfaceTriangle()
:NgoGeoSurface()
{
   NgoComponent::create();
}

NgoGeoSurfaceTriangle::NgoGeoSurfaceTriangle(double side1, double side2, double side3)
:NgoGeoSurface()
{
   NgoComponent::create();
   this->side1 = side1;
   this->side2 = side2;
   this->side3 = side3;
}

bool NgoGeoSurfaceTriangle::create(NgoObj::NgoComponent & geometry)
{
   if (geometry.hasVariableNamed("SIDE1"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("SIDE1").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      side1 = q();
       if (geometry.hasVariableNamed("SIDE2"))
       {
          NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("SIDE2").front();
          NgoQuantity q = vq->getValue();
          q.convert();
          side2 = q();
           if (geometry.hasVariableNamed("SIDE3"))
           {
              NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("SIDE3").front();
              NgoQuantity q = vq->getValue();
              q.convert();
              side3 = q();
              return true;
           }
       }
   }
   return false;
}

double NgoGeoSurfaceTriangle::doComputeSurface()
{
   double p = side1.modulated() + side2.modulated() + side3.modulated();
   p *= 0.5;
   return sqrt( (p-side1.modulated()) * (p-side2.modulated()) * (p-side3.modulated()) * p );
}

double NgoGeoSurfaceTriangle::doComputePerimeter()
{
   return (double) side1.modulated() + side2.modulated() + side3.modulated();
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoSurfRegisterTriangle(double side1, double side2, double side3)
{
   try
   {
      NgoGeoSurface * surf = new NgoGeoSurfaceTriangle(side1,side2,side3);
      if (!surf)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfRegisterTriangle")
   return -1;
}

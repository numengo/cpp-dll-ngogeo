/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceRectangle.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoSurfaceRectangleDef "Geometry".
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

#include "ngogeo/NgoGeoSurfaceRectangle.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_SURFACE(NgoGeo::NgoGeoSurfaceRectangle,"Description of a rectangular surface","NgoGeoSurfaceRectangleType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoSurfaceRectangle DEFINITION
*******************************************************************************/
REGISTER_SURFACE(NgoGeoSurfaceRectangle);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoSurfaceRectangle, NgoGeoSurface)

NgoGeoSurfaceRectangle::NgoGeoSurfaceRectangle()
:NgoGeoSurface()
{
   NgoComponent::create();
}

NgoGeoSurfaceRectangle::NgoGeoSurfaceRectangle(double side1, double side2)
:NgoGeoSurface()
{
   NgoComponent::create();
   this->side1 = side1;
   this->side2 = side2;
}


bool NgoGeoSurfaceRectangle::create(NgoObj::NgoComponent & geometry)
{
   std::vector<double> params;
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
          return true;
       }
   }
   return false;
}


double NgoGeoSurfaceRectangle::doComputeSurface()
{
    return (double) side1.modulated() * side2.modulated();
}

double NgoGeoSurfaceRectangle::doComputePerimeter()
{
    return (double) 2. * (side1.modulated() + side2.modulated() );
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoSurfRegisterRectangle(double side1, double side2)
{
   try
   {
      NgoGeoSurface * surf = new NgoGeoSurfaceRectangle(side1,side2);
      if (!surf)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfRegisterRectangle")
   return -1;
}

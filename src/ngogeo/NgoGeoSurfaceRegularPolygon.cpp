/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceRegularPolygon.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoSurfaceRegularPolygonDef "Geometry".
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

#include "ngogeo/NgoGeoSurfaceRegularPolygon.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_SURFACE(NgoGeo::NgoGeoSurfaceRegularPolygon,"Description of a regular polygon surface","NgoGeoSurfaceRegularPolygonType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoSurfaceRegularPolygon DEFINITION
*******************************************************************************/
REGISTER_SURFACE(NgoGeoSurfaceRegularPolygon);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoSurfaceRegularPolygon, NgoGeoSurface)



NgoGeoSurfaceRegularPolygon::NgoGeoSurfaceRegularPolygon()
:NgoGeoSurface()
{
   NgoComponent::create();
}

NgoGeoSurfaceRegularPolygon::NgoGeoSurfaceRegularPolygon(double side, int nside)
:NgoGeoSurface()
{
   NgoComponent::create();
   this->nside = nside;
   this->side  = side;
}

bool NgoGeoSurfaceRegularPolygon::create(NgoObj::NgoComponent & geometry)
{
   std::vector<double> params;
   if (geometry.hasVariableNamed("SIDE"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("SIDE").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      side = q();
       if (geometry.hasVariableNamed("NSIDE"))
       {
          NgoVariableInteger * vq = (NgoVariableInteger *) geometry.getVariableNamed("NSIDE").front();
          variableInteger q = vq->getValue();
          nside = q();
       }
   }
   return false;
}

double NgoGeoSurfaceRegularPolygon::doComputeSurface()
{
    return (double) side.modulated() * side.modulated() * nside() / 4. / tan(d_pi / nside());
}

double NgoGeoSurfaceRegularPolygon::doComputePerimeter()
{
    return (double) side.modulated() * nside();
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoSurfRegisterRegularPolygon(double side, int nside)
{
   try
   {
      NgoGeoSurface * surf = new NgoGeoSurfaceRegularPolygon(side,nside);
      if (!surf)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfRegisterRegularPolygon")
   return -1;
}

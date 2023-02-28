/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceRightCylinder.cpp
@author Cedric ROMAN - roman@numengo.com
@date August 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoSurfaceRightCylinderDef "Geometry".
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

#include "ngogeo/NgoGeoSurfaceRightCylinder.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_SURFACE(NgoGeo::NgoGeoSurfaceRightCylinder,"Description of a right cylinder surface","NgoGeoSurfaceRightCylinderType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoSurfaceRightCylinder DEFINITION
*******************************************************************************/
REGISTER_SURFACE(NgoGeoSurfaceRightCylinder);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoSurfaceRightCylinder, NgoGeoSurface)

NgoGeoSurfaceRightCylinder::NgoGeoSurfaceRightCylinder()
:NgoGeoSurface(),base(0L)
{
   NgoComponent::create();
}

NgoGeoSurfaceRightCylinder::NgoGeoSurfaceRightCylinder(NgoGeoSurface & base, double length)
:NgoGeoSurface(),base(0L)
{
   NgoComponent::create();
   setBaseSurface(base);
   this->length = length;
}

bool NgoGeoSurfaceRightCylinder::create(NgoObj::NgoComponent & geometry)
{
   NgoComponent::create();
   if (geometry.hasVariableNamed("LENGTH"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("LENGTH").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      length = q();
      if (geometry.hasVariableNamed("BASE"))
      {
          base = NgoGeoSurfaceManager::get()->create( *dynamic_cast<NgoObj::NgoComponent *>(geometry.getVariableNamed("BASE").front()));
          return true;
      }
   }
   return false;
}

double NgoGeoSurfaceRightCylinder::doComputeSurface()
{
    return (double) length.modulated() * base->perimeter();
}

double NgoGeoSurfaceRightCylinder::doComputePerimeter()
{
    return (double) 2. * base->perimeter();
}

} // namespace NgoGeo


using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoSurfRegisterRightCylinder(int surfb, double height)
{
   try
   {
      if (!((surfb < getSurfaces().size())&&(surfb>=0)))
         return -1;

      NgoGeoSurface * surf = new NgoGeoSurfaceRightCylinder(*getSurface(surfb),height);
      if (!surf)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfRegisterRightCylinder")
   return -1;
}

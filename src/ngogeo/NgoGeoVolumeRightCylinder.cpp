/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolumeRightCylinder.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoVolumeRightCylinderDef "Geometry".
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

#include "ngogeo/NgoGeoVolumeRightCylinder.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_VOLUME(NgoGeo::NgoGeoVolumeRightCylinder,"Description of a volume of right cylinder","NgoGeoVolumeRightCylinderType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoVolumeRightCylinder DEFINITION
*******************************************************************************/
REGISTER_VOLUME(NgoGeoVolumeRightCylinder);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoVolumeRightCylinder, NgoGeoVolume)

NgoGeoVolumeRightCylinder::NgoGeoVolumeRightCylinder()
:NgoGeoVolume(),base(0L)
{
   NgoComponent::create();
}

NgoGeoVolumeRightCylinder::NgoGeoVolumeRightCylinder(NgoGeoSurface & base, double length)
:NgoGeoVolume(),base(0L)
{
   NgoComponent::create();
   this->base = & base;
   this->length = length;
}

bool NgoGeoVolumeRightCylinder::create(NgoObj::NgoComponent & geometry)
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

double NgoGeoVolumeRightCylinder::doComputeVolume()
{
    base->surface.update();
    return (double) length.modulated() * base->surface();
}

double NgoGeoVolumeRightCylinder::doComputeSurface()
{
    base->perimeter.update();
    return (double) length.modulated() * base->perimeter();
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoVolRegisterRightCylinder(int surf, double height)
{
   try
   {
      if (!((surf < getSurfaces().size())&&(surf>=0)))
         return -1;

      NgoGeoVolume * vol = new NgoGeoVolumeRightCylinder(*getSurface(surf),height);
      if (!vol)
         return -1;
      return (getVolumes().size()-1);
   }
   CATCH_GEO("NgoGeoVolRegisterRightCylinder")
   return -1;
}


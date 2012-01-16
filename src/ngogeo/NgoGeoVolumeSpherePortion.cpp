/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolumeSpherePortion.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoVolumeSpherePortionDef "Geometry".
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

#include "ngogeo/NgoGeoVolumeSpherePortion.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_VOLUME(NgoGeo::NgoGeoVolumeSpherePortion,"Description of a volume of sphere portion","NgoGeoVolumeSpherePortionType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoVolumeSpherePortion DEFINITION
*******************************************************************************/
REGISTER_VOLUME(NgoGeoVolumeSpherePortion);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoVolumeSpherePortion, NgoGeoVolume)

NgoGeoVolumeSpherePortion::NgoGeoVolumeSpherePortion()
:NgoGeoVolume()
{
   NgoComponent::create();
}

NgoGeoVolumeSpherePortion::NgoGeoVolumeSpherePortion(double diameter, double heigth)
:NgoGeoVolume()
{
   NgoComponent::create();
   this->diameter  = diameter;
   this->height    = height;
}

bool NgoGeoVolumeSpherePortion::create(NgoObj::NgoComponent & geometry)
{
   std::vector<double> params;
   if (geometry.hasVariableNamed("DIAMETER"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("DIAMETER").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      diameter = q();
       if (geometry.hasVariableNamed("HEIGHT"))
       {
          NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("HEIGHT").front();
          NgoQuantity q = vq->getValue();
          q.convert();
          height = q();
          return true;
       }
   }
   return false;
}

double NgoGeoVolumeSpherePortion::doComputeVolume()
{
    double d = diameter.modulated();
    double h = height.modulated();
    return d * d * d_pi / 3 * (3. * 0.5 * h - d);
}

double NgoGeoVolumeSpherePortion::doComputeSurface()
{
    double d = diameter.modulated();
    double h = height.modulated();
    return d * h * d_pi;
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoVolRegisterSpherePortion(double diam, double height)
{
   try
   {
      NgoGeoVolume * vol = new NgoGeoVolumeSpherePortion(diam,height);
      if (!vol)
         return -1;
      return (getVolumes().size()-1);
   }
   CATCH_GEO("NgoGeoVolRegisterSpherePortion")
   return -1;
}


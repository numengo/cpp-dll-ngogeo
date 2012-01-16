/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolumeConeFrustum.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoVolumeConeFrustumDef "Geometry".
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

#include "ngogeo/NgoGeoVolumeConeFrustum.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_VOLUME(NgoGeo::NgoGeoVolumeConeFrustum,"Description of a volume of cone frustum","NgoGeoVolumeConeFrustumType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoVolumeConeFrustum DEFINITION
*******************************************************************************/
REGISTER_VOLUME(NgoGeoVolumeConeFrustum);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoVolumeConeFrustum, NgoGeoVolume)


NgoGeoVolumeConeFrustum::NgoGeoVolumeConeFrustum()
:NgoGeoVolume()
{
   NgoComponent::create();
}

NgoGeoVolumeConeFrustum::NgoGeoVolumeConeFrustum(double diameter1, double heigth, double diameter2)
:NgoGeoVolume()
{
   NgoComponent::create();
   this->diameter1 = diameter1;
   this->diameter2 = diameter2;
   this->height    = height;
}


bool NgoGeoVolumeConeFrustum::create(NgoObj::NgoComponent & geometry)
{
   if (geometry.hasVariableNamed("DIAMETER1"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("DIAMETER1").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      diameter1 = q();
       if (geometry.hasVariableNamed("HEIGHT"))
       {
          NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("HEIGHT").front();
          NgoQuantity q = vq->getValue();
          q.convert();
          height = q();
           if (geometry.hasVariableNamed("DIAMETER2"))
           {
              NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("DIAMETER2").front();
              NgoQuantity q = vq->getValue();
              q.convert();
              diameter2 = q();
           }
           return true;
       }
   }
   return false;
}

double NgoGeoVolumeConeFrustum::doComputeVolume()
{
   double D1 = diameter1.modulated();
   double D2 = diameter2.modulated();
   double h  = height.modulated();
   return (double) d_pi / 12. * h * (D1 * D1 + D1 * D2 + D2 * D2);
}

double NgoGeoVolumeConeFrustum::doComputeSurface()
{
   double D1 = diameter1.modulated();
   double D2 = diameter2.modulated();
   double h  = height.modulated();
   return  d_pi * 0.5 * (D1 + D2) * sqrt(h * h + (D1 - D2) * (D1 - D2));
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoVolRegisterConeFrustum(double diam1, double height, double diam2)
{
   try
   {
      NgoGeoVolume * vol = new NgoGeoVolumeConeFrustum(diam1, height, diam2);
      if (!vol)
         return -1;
      return (getVolumes().size()-1);
   }
   CATCH_GEO("NgoGeoVolRegisterConeFrustum")
   return -1;
}


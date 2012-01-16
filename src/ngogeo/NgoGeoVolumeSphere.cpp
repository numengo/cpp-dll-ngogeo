/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolumeSphere.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoVolumeSphereDef "Geometry".
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

#include "ngogeo/NgoGeoVolumeSphere.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_VOLUME(NgoGeo::NgoGeoVolumeSphere,"Description of a volume of sphere","NgoGeoVolumeSphereType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoVolumeSphere DEFINITION
*******************************************************************************/
REGISTER_VOLUME(NgoGeoVolumeSphere);
IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoVolumeSphere, NgoGeoVolume)


NgoGeoVolumeSphere::NgoGeoVolumeSphere()
:NgoGeoVolume()
{
   NgoComponent::create();
}

NgoGeoVolumeSphere::NgoGeoVolumeSphere(double diameter)
:NgoGeoVolume()
{
   NgoComponent::create();
   this->diameter = diameter;
}


bool NgoGeoVolumeSphere::create(NgoObj::NgoComponent & geometry)
{
   if (geometry.hasVariableNamed("DIAMETER"))
   {
      NgoVariableReal * vq = (NgoVariableReal *) geometry.getVariableNamed("DIAMETER").front();
      NgoQuantity q = vq->getValue();
      q.convert();
      diameter = q();
      return true;
   }
   return false;
}

double NgoGeoVolumeSphere::doComputeVolume()
{
    double d = diameter.modulated();
//    double d = diameter();
    return d_pi / 6. * d * d * d;
}

double NgoGeoVolumeSphere::doComputeSurface()
{
    double d = diameter.modulated();
    return d_pi * d * d;
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/

int NgoGeoVolRegister(double vol)
{
   try
   {
      double diam = pow(6.*fabs(vol)/d_pi,1./3.);
      return NgoGeoVolRegisterSphere(diam);
   }
   CATCH_GEO("NgoGeoVolRegister")
   return -1;
}

int NgoGeoVolRegisterSphere(double diam)
{
   try
   {
      NgoGeoVolume * vol = new NgoGeoVolumeSphere(diam);
      if (!vol)
         return -1;
      return (getVolumes().size()-1);
   }
   CATCH_GEO("NgoGeoVolRegisterSphere")
   return -1;
}

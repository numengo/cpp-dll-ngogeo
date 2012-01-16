/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeo_wrapperC.cpp
@author Cedric ROMAN - roman@numengo.com
@date september 2010 from NgoGeoGeo
@brief File containing all generic geometry functions C wrapper
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
   REVISIONS
*******************************************************************************/

/*******************************************************************************
   INCLUDES
*******************************************************************************/
#include "ngoerr/NgoError.h"

#include "ngocommon/NgoFileHandler.h"
#include "ngocommon/NgoSingletonManager.h"

#include "ngoxml/NgoXmlResource.h"

#include "ngogeo/NgoGeo_wrapperC.h"

#include "ngocommon/NgoCommon.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>


using namespace NgoGeo;

/*******************************************************************************
    SURFACE FUNCTIONS
*******************************************************************************/


int NgoGeoSurfDuplicate(int surf)
{
   try
   {
      if (!((surf < getSurfaces().size())&&(surf>=0)))
         return -1;
      NgoGeoSurface * clone = getSurface(surf)->clone();
      if (!clone)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfDuplicate")
   return -1;
}

double NgoGeoSurfComputeSurface(int surf)
{
   try
   {
      if (((surf < getSurfaces().size())&&(surf>=0)))
         return getSurface(surf)->computeSurface();
      return UNDEF;
   }
   CATCH_GEO("NgoGeoSurfComputeSurface")
   return UNDEF;
}

double NgoGeoSurfComputePerimeter(int surf)
{
   try
   {
      if (((surf < getSurfaces().size())&&(surf>=0)))
         return getSurface(surf)->computePerimeter();
   }
   CATCH_GEO("NgoGeoSurfComputePerimeter")
   return UNDEF;
}

double NgoGeoSurfComputeHydraulicDiameter(int surf)
{
   try
   {
      if (((surf < getSurfaces().size())&&(surf>=0)))
         return getSurface(surf)->computeHydraulicDiameter();
   }
   CATCH_GEO("NgoGeoSurfComputeHydraulicDiameter")
   return UNDEF;
}

void NgoGeoSurfSetHydraulicDiameter(int surf, double diam)
{
   try
   {
      if (((surf < getSurfaces().size())&&(surf>=0)))
         return getSurface(surf)->setHydraulicDiameter(diam);
   }
   CATCH_GEO("NgoGeoSurfSetHydraulicDiameter")
}

void NgoGeoSurfSetModulatedParam(int surf, const char * param)
{
   try
   {
      if (((surf < getSurfaces().size())&&(surf>=0)))
         return getSurface(surf)->setModulatedParameter(param);
   }
   CATCH_GEO("NgoGeoSurfSetModulatedParam")
}

void NgoGeoSurfModulate(int surf, double module)
{
   try
   {
      if (((surf < getSurfaces().size())&&(surf>=0)))
         return getSurface(surf)->setOverallModule(module);
   }
   CATCH_GEO("NgoGeoSurfModulate")
}

/*******************************************************************************
    VOLUME FUNCTIONS
*******************************************************************************/

int NgoGeoVolDuplicate(int vol)
{
   try
   {
      if (!((vol < getVolumes().size())&&(vol>=0)))
         return -1;
      NgoGeoVolume * clone = getVolume(vol)->clone();
      if (!clone)
         return -1;
      return (getVolumes().size()-1);
   }
   CATCH_GEO("NgoGeoVolDuplicate")
   return -1;
}

double NgoGeoVolComputeSurface(int vol)
{
   try
   {
      if ((vol < getVolumes().size())&&(vol>=0))
         return getVolume(vol)->computeSurface();
   }
   CATCH_GEO("NgoGeoVolComputeSurface")
   return UNDEF;
}

double NgoGeoVolComputeVolume(int vol)
{
   try
   {
      if ((vol < getVolumes().size())&&(vol>=0))
         return getVolume(vol)->computeVolume();
   }
   CATCH_GEO("NgoGeoVolComputeVolume")
   return UNDEF;
}

void NgoGeoVolSetModulatedParam(int vol, const char * param)
{
   try
   {
      if ((vol < getVolumes().size())&&(vol>=0))
         return getVolume(vol)->setModulatedParameter(param);
   }
   CATCH_GEO("NgoGeoVolSetModulatedParam")
}

void NgoGeoVolModulate(int vol, double module)
{
   try
   {
      if ((vol < getVolumes().size())&&(vol>=0))
         return getVolume(vol)->setOverallModule(module);
   }
   CATCH_GEO("NgoGeoSurfRegisterDisk")
}

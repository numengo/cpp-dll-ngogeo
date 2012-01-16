/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfacePorousMatrixFiber.cpp
@author Cedric ROMAN - roman@numengo.com
@date September 2011
@brief File containing generic classes  member definitions for a @ref PageNgoGeoSurfacePorousMatrixFiberDef "Geometry".
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

#include "ngogeo/NgoGeoSurfacePorousMatrixFiber.h"

#include "ngosim/NgoFmiExport.cpp"

DESCRIPTION_SURFACE(NgoGeo::NgoGeoSurfacePorousMatrixFiber,"Description of a porous media surface for fiber matrixes","NgoGeoSurfacePorousMatrixFiberType")

namespace NgoGeo {

using namespace NgoObj;

/*******************************************************************************
   CLASS NgoGeoSurfacePorousMatrixFiber DEFINITION
*******************************************************************************/
REGISTER_SURFACE(NgoGeoSurfacePorousMatrixFiber);

IMPLEMENT_DYNAMIC_CLASS_NGO(NgoGeoSurfacePorousMatrixFiber, NgoGeoSurface)

NgoGeoSurfacePorousMatrixFiber::NgoGeoSurfacePorousMatrixFiber()
:NgoGeoSurface(),base_(0L)
{
   NgoComponent::create();
}

NgoGeoSurfacePorousMatrixFiber::NgoGeoSurfacePorousMatrixFiber(NgoGeoSurface * base, double dw, double B)
:NgoGeoSurface()
{
   NgoComponent::create();
   setBaseSurface(*base);
   this->dw_ = dw;
   this->B_  = B;
}

bool NgoGeoSurfacePorousMatrixFiber::create(NgoObj::NgoComponent & geometry)
{
   return false;
}

double NgoGeoSurfacePorousMatrixFiber::doComputeSurface()
{
    return base_->computeSurface()  * B_();
}

double NgoGeoSurfacePorousMatrixFiber::doComputePerimeter()
{
    return (double) 4. * (1. - B_()) * base_->computeSurface() / dw_();
}

} // namespace NgoGeo

using namespace NgoGeo;

/*******************************************************************************
    C constructors
*******************************************************************************/
int NgoGeoSurfRegisterPorousMatrixFiber(int surfind, double dw, double B)
{
   try
   {
      NgoGeoSurface * surf = new NgoGeoSurfacePorousMatrixFiber(getSurface(surfind),dw,B);
      if (!surf)
         return -1;
      return (getSurfaces().size()-1);
   }
   CATCH_GEO("NgoGeoSurfRegisterPorousMatrixFiber")
   return -1;
}

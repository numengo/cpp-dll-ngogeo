#ifndef _NgoGeo_wrapperC_h_
#define _NgoGeo_wrapperC_h_

/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeo_wrapperC.h
@author Cedric ROMAN - roman@numengo.com
@date september 2010
@brief File containing all prototypes of geometry functions related to the Numengo Fluid Library
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
#include "ngogeo/NgoGeoSurface.h"

#include "ngogeo/NgoGeoSurfaceDisk.h"
#include "ngogeo/NgoGeoSurfaceEllipse.h"
#include "ngogeo/NgoGeoSurfaceRectangle.h"
#include "ngogeo/NgoGeoSurfaceRegularPolygon.h"
#include "ngogeo/NgoGeoSurfaceRightCylinder.h"
#include "ngogeo/NgoGeoSurfaceRing.h"
#include "ngogeo/NgoGeoSurfaceTriangle.h"

#include "ngogeo/NgoGeoVolume.h"

#include "ngogeo/NgoGeoVolumeConeFrustum.h"
#include "ngogeo/NgoGeoVolumeRightCylinder.h"
#include "ngogeo/NgoGeoVolumeSphere.h"
#include "ngogeo/NgoGeoVolumeSpherePortion.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
    SURFACE FUNCTIONS
*******************************************************************************/
/*! @brief function to clone an existing surface
It is a C wrapper to NgoGeo::NgoGeoSurface::clone()
@param surf surface index to clone
@return cloned surface index
@ingroup GroupNgoGeoWrapperCSurf
*/
NGOGEO_EXPORT int NgoGeoSurfDuplicate(int surf);

/*! @brief function to compute the surface
It is a C wrapper to NgoGeo::NgoGeoSurface::computeSurface()
@param surf surface index
@return surface value
@ingroup GroupNgoGeoWrapperCSurf
*/
NGOGEO_EXPORT double NgoGeoSurfComputeSurface(int surf);

/*! @brief function to compute the perimeter
It is a C wrapper to NgoGeo::NgoGeoSurface::computePerimeter()
@param surf surface index
@return perimeter value
@ingroup GroupNgoGeoWrapperCSurf
*/
NGOGEO_EXPORT double NgoGeoSurfComputePerimeter(int surf);

/*! @brief function to compute the hydraulic diameter
It is a C wrapper to NgoGeo::NgoGeoSurface::computeHydraulicDiameter()
@param surf surface index
@return hydraulic diameter value
@ingroup GroupNgoGeoWrapperCSurf
*/
NGOGEO_EXPORT double NgoGeoSurfComputeHydraulicDiameter(int surf);

/*! @brief function to set a user defined hydraulic diameter
It is a C wrapper to NgoGeo::NgoGeoSurface::setHydraulicDiameter()
@param surf surface index
@param diam hydraulic diameter value
@ingroup GroupNgoGeoWrapperCSurf
*/
NGOGEO_EXPORT void NgoGeoSurfSetHydraulicDiameter(int surf, double diam);

/*! @brief function to define a modulated parameter of the surface
It is a C wrapper to NgoGeo::NgoGeoGeometry::setModulatedParameter()
@param surf surface index
@param param surface parameter identifier
@ingroup GroupNgoGeoWrapperCSurf
*/
NGOGEO_EXPORT void NgoGeoSurfSetModulatedParam(int surf, const char * param);

/*! @brief function to modulate the parameter of the surface defined byNgoGeoSurfSetModulatedParam
It is a C wrapper to NgoGeo::NgoGeoGeometry::setModule()
@param surf surface index
@param module module to set
@ingroup GroupNgoGeoWrapperCSurf
*/
NGOGEO_EXPORT void NgoGeoSurfModulate(int surf, double module);

 /*! @defgroup GroupNgoGeoWrapperCSurfAvl Available Descriptions
 @ingroup GroupNgoGeoWrapperCSurf
 */

/*******************************************************************************
    VOLUME FUNCTIONS
*******************************************************************************/

/*! @brief function to clone an existing volume
It is a C wrapper to NgoGeo::NgoGeoVolume::clone()
@param vol volume index to clone
@return cloned volume index
@ingroup GroupNgoGeoWrapperCVol
*/
NGOGEO_EXPORT int NgoGeoVolDuplicate(int vol);

/*! @brief function to compute the surface envelop of a volume
It is a C wrapper to NgoGeo::NgoGeoVolume::computeSurface()
@param vol volume index
@return surface value
@ingroup GroupNgoGeoWrapperCVol
*/
NGOGEO_EXPORT double NgoGeoVolComputeSurface(int vol);

/*! @brief function to compute the volume
It is a C wrapper to NgoGeo::NgoGeoVolume::computeVolume()
@param vol volume index to clone
@return surface value
@ingroup GroupNgoGeoWrapperCVol
*/
NGOGEO_EXPORT double NgoGeoVolComputeVolume(int vol);

/*! @brief function to define a modulated parameter of the volume
It is a C wrapper to NgoGeo::NgoGeoGeometry::setModulatedParameter()
@param vol volume index to clone
@param param surface parameter identifier
@ingroup GroupNgoGeoWrapperCVol
*/
NGOGEO_EXPORT void NgoGeoVolSetModulatedParam(int vol, const char * param);

/*! @brief function to modulate the parameter of the volume defined byNgoGeoVolSetModulatedParam
It is a C wrapper to NgoGeo::NgoGeoGeometry::setModule()
@param vol volume index to clone
@param module module to set
@ingroup GroupNgoGeoWrapperCVol
*/
NGOGEO_EXPORT void NgoGeoVolModulate(int vol, double module);

 /*! @defgroup GroupNgoGeoWrapperCVolAvl Available Descriptions
 @ingroup GroupNgoGeoWrapperCVol
 */

#ifdef __cplusplus
} // extern C
#endif

#endif

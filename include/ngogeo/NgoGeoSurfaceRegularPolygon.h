#ifndef _NgoGeoSurfaceRegularPolygon_h
#define _NgoGeoSurfaceRegularPolygon_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceRegularPolygon.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoSurfaceRegularPolygon
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
   C DECLARATIONS
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

const int vr_NgoGeoSurfaceRegularPolygon_side       = 0;
const int vr_NgoGeoSurfaceRegularPolygon_sideModule = 100;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a regular polygon surface
It is a C wrapper to NgoGeo::NgoGeoSurfaceRegularPolygon
@param side polygon side length
@param nside number of sides
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGO_GEO_EXPORT int NgoGeoSurfRegisterRegularPolygon(double side, int nside);

#ifdef __cplusplus
} // end extern "C"

/*******************************************************************************
   INCLUDES
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "ngogeo/NgoGeoSurface.h"

/*******************************************************************************
   DEFINES / TYPDEFS / ENUMS
*******************************************************************************/
namespace NgoGeo {

/*******************************************************************************
   CLASS NgoGeoSurfaceRegularPolygon DECLARATION
*******************************************************************************/
/*!
@class NgoGeoSurfaceRegularPolygon
@brief class NgoGeoSurface to compute surface and perimeter of a regular polygon
\image html regular_polygon.png
\image latex regular_polygon.png
@ingroup GroupNgoGeoSurface
*/
class NGO_GEO_EXPORT NgoGeoSurfaceRegularPolygon : public NgoGeoSurface, public NgoGeoSurfaceModule<NgoGeoSurfaceRegularPolygon>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoSurfaceRegularPolygon )

public :
   /*! @brief base constructor */
   NgoGeoSurfaceRegularPolygon();
   /*! @brief Constructor
      \image html regular_polygon.png
      \image latex regular_polygon.png
   */
   /*! @param side side of the polygon (a) */
   /*! @param nside number of sides of the polygon */
   NgoGeoSurfaceRegularPolygon(double side, int nside);
    /*! @brief copy constructor */
   NgoGeoSurfaceRegularPolygon(const NgoGeoSurfaceRegularPolygon & rhs)
   :NgoGeoSurface(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoSurfaceRegularPolygon & operator=(const NgoGeoSurfaceRegularPolygon & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoSurface::operator=(rhs);
           this->side  = rhs.side;
           this->nside = rhs.nside;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoSurfaceRegularPolygon * clone() const { return new NgoGeoSurfaceRegularPolygon(*this);};
   /*! method to set parameters from input arrays */
   /*! should be overloaded */
   virtual bool create(const double rp[], size_t nrp,
                        const int ip[], size_t nip,
                        const bool bp[], size_t nbp,
                        const char * tp[], size_t ntp
                        )
    {
        doCreate();
        side  = rp[0];
        nside = ip[0];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

protected:
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoSurfaceRegularPolygon");
        registerVariableWithReference(vr_NgoGeoSurfaceRegularPolygon_side,side);
        registerVariableWithReference(vr_NgoGeoSurfaceRegularPolygon_sideModule,side.module);
        associateMethodToVariable1(surface,NgoGeoSurfaceRegularPolygon,doCalcSurface,side.modulated);
        associateMethodToVariable1(perimeter,NgoGeoSurfaceRegularPolygon,doCalcPerimeter,side.modulated);

        registerPort(portSideModule);
        portSideModule.addVariable(side.module);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputePerimeter();

    // parameter variables
    protected : parameterInteger nside;
    public : modulatedParameterReal side;
    public : NgoSim::NgoPort portSideModule;
};

} // namespace NgoGeo

#endif // end of ifdef __cplusplus

/*******************************************************************************
   C DECLARATIONS
*******************************************************************************/
// set of macros to suppress warnings when redefining model identifier, when including
// multiple header files
#ifdef MODEL_IDENTIFIER
    #undef MODEL_IDENTIFIER
#endif
#ifdef MODEL_GUID
    #undef MODEL_GUID
#endif
#define MODEL_IDENTIFIER NgoGeoSurfaceRegularPolygon
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


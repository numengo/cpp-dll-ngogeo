#ifndef _NgoGeoSurfaceDisk_h
#define _NgoGeoSurfaceDisk_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceDisk.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoSurface for a disk
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

const int vr_NgoGeoSurfaceDisk_diameter          = 0;
const int vr_NgoGeoSurfaceDisk_diameterModule    = 100;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a surface with no specified geometry. It actually creates a sphere of equivalent volume using NgoGeo::NgoGeoVolumeSphere
@param surf surface value
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGO_GEO_EXPORT int NgoGeoSurfRegister(double surf);

/*! @brief function to register a disk surface
It is a C wrapper to NgoGeo::NgoGeoSurfaceDisk
@param diam disk diameter
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGO_GEO_EXPORT int NgoGeoSurfRegisterDisk(double diam);

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
   CLASS NgoGeoSurfaceDisk DECLARATION
*******************************************************************************/
/*!
@class NgoGeoSurfaceDisk
@brief class NgoGeoSurface to compute surface and perimeter of a disk
\image html circle.png
\image latex circle.png
@ingroup GroupNgoGeoSurface
*/
class NGO_GEO_EXPORT NgoGeoSurfaceDisk : public NgoGeoSurface, public NgoGeoSurfaceModule<NgoGeoSurfaceDisk>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoSurfaceDisk )

public :
   /*! @brief base constructor */
   NgoGeoSurfaceDisk();
   /*! @brief Constructor
      \image html circle.png
      \image latex circle.png   */
   /*! @param diam diameter of disk (diam = 2 r ) */
   NgoGeoSurfaceDisk(double diameter);
   /*! @brief copy constructor */
   NgoGeoSurfaceDisk(const NgoGeoSurfaceDisk & rhs)
   :NgoGeoSurface(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoSurfaceDisk & operator=(const NgoGeoSurfaceDisk & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoSurface::operator=(rhs);
           this->diameter = rhs.diameter;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoSurfaceDisk * clone() const { return new NgoGeoSurfaceDisk(*this);};
   /*! method to set parameters from input arrays */
   /*! should be overloaded */
   virtual bool create(const double rp[], size_t nrp,
                        const int ip[], size_t nip,
                        const bool bp[], size_t nbp,
                        const char * tp[], size_t ntp
                        )
    {
        doCreate();
        diameter = rp[0];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

protected:
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoSurfaceDisk");
        registerVariableWithReference(vr_NgoGeoSurfaceDisk_diameter,diameter);
        registerVariableWithReference(vr_NgoGeoSurfaceDisk_diameterModule,diameter.module);
        associateMethodToVariable1(surface,NgoGeoSurfaceDisk,doCalcSurface,diameter.modulated);
        associateMethodToVariable1(perimeter,NgoGeoSurfaceDisk,doCalcPerimeter,diameter.modulated);

        registerPort(portDiameterModule);
        portDiameterModule.addVariable(diameter.module);
    };
    /*! @brief method to actually overload and define by user */
    virtual void doCalcMain() { doCalcSurface(); };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputePerimeter();

    // parameter variables
    public : modulatedParameterReal diameter;
    public : NgoSim::NgoPort portDiameterModule;
};

}; // namespace NgoGeo

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
#define MODEL_IDENTIFIER NgoGeoSurfaceDisk
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif

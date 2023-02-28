#ifndef _NgoGeoSurfaceRing_h
#define _NgoGeoSurfaceRing_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceRing.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoSurfaceRing
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

const int vr_NgoGeoSurfaceRing_diameter1          = 0;
const int vr_NgoGeoSurfaceRing_diameter2          = 1;
const int vr_NgoGeoSurfaceRing_diameter1Module    = 100;
const int vr_NgoGeoSurfaceRing_diameter2Module    = 101;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a ring surface
It is a C wrapper to NgoGeo::NgoGeoSurfaceRing
@param diam1 inner diameter
@param diam2 outer diameter
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGO_GEO_EXPORT int NgoGeoSurfRegisterRing(double diam1, double diam2);

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
   CLASS NgoGeoSurfaceRing DECLARATION
*******************************************************************************/
/*!
@class NgoGeoSurfaceRing
@brief class NgoGeoSurface to compute surface and perimeter of a ring
\image html right_cylinder.png
\image latex right_cylinder.png
@ingroup GroupNgoGeoSurface
*/
class NGO_GEO_EXPORT NgoGeoSurfaceRing : public NgoGeoSurface, public NgoGeoSurfaceModule<NgoGeoSurfaceRing>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoSurfaceRing )

public :
   /*! @brief base constructor */
   NgoGeoSurfaceRing();
   /*! @brief Constructor
      \image html ring.png
      \image latex ring.png
   */
   /*! @param diam1 inner diameter of disk (diam1=2 rin)*/
   /*! @param diam2 outer diameter of disk (diam2=2 rout)*/
   NgoGeoSurfaceRing(double diam1, double diam2);
   /*! @brief copy constructor */
   NgoGeoSurfaceRing(const NgoGeoSurfaceRing & rhs)
   :NgoGeoSurface(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoSurfaceRing & operator=(const NgoGeoSurfaceRing & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoSurface::operator=(rhs);
           this->diameter1 = rhs.diameter1;
           this->diameter2 = rhs.diameter2;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoSurfaceRing * clone() const { return new NgoGeoSurfaceRing(*this);};
   /*! method to set parameters from input arrays */
   /*! should be overloaded */
   virtual bool create(const double rp[], size_t nrp,
                        const int ip[], size_t nip,
                        const bool bp[], size_t nbp,
                        const char * tp[], size_t ntp
                        )
    {
        doCreate();
        this->diameter1 = rp[0];
        this->diameter2 = rp[1];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

protected:
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoSurfaceRing");
        registerVariableWithReference(vr_NgoGeoSurfaceRing_diameter1      ,diameter1      );
        registerVariableWithReference(vr_NgoGeoSurfaceRing_diameter2      ,diameter2      );
        registerVariableWithReference(vr_NgoGeoSurfaceRing_diameter1Module,diameter1.module);
        registerVariableWithReference(vr_NgoGeoSurfaceRing_diameter2Module,diameter2.module);

        associateMethodToVariable2(surface,NgoGeoSurfaceRing,doCalcSurface,diameter1.modulated,diameter2.modulated);
        associateMethodToVariable2(perimeter,NgoGeoSurfaceRing,doCalcPerimeter,diameter1.modulated,diameter2.modulated);

        registerPort(portDiameter1Module);
        portDiameter1Module.addVariable(diameter1.module);
        registerPort(portDiameter2Module);
        portDiameter2Module.addVariable(diameter2.module);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputePerimeter();

    // parameter variables
    public : modulatedParameterReal diameter1, diameter2;
    public : NgoSim::NgoPort portDiameter1Module, portDiameter2Module;
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
#define MODEL_IDENTIFIER NgoGeoSurfaceRing
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


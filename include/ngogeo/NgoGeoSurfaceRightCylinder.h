#ifndef _NgoGeoSurfaceRightCylinder_h
#define _NgoGeoSurfaceRightCylinder_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceRightCylinder.h
@author Cedric ROMAN - roman@numengo.com
@date August 2009
@brief File containing definition of a class for a NgoGeoSurfaceRightCylinder
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

const int vr_NgoGeoSurfaceRightCylinder_length          = 0;
const int vr_NgoGeoSurfaceRightCylinder_lengthModule    = 100;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a right cylinder surface
It is a C wrapper to NgoGeo::NgoGeoSurfaceRightCylinder
@param surf base surface index
@param height  cylinder length
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGO_GEO_EXPORT int NgoGeoSurfRegisterRightCylinder(int surf, double height);

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
   CLASS NgoGeoSurfaceRightCylinder DECLARATION
*******************************************************************************/
/*!
@class NgoGeoSurfaceRightCylinder
@brief class NgoGeoSurface to compute surface and perimeter of a right cylinder
\image html right_cylinder.png
\image latex right_cylinder.png
@sa NgoGeoVolumeRightCylinder
@ingroup GroupNgoGeoSurface
*/
class NGO_GEO_EXPORT NgoGeoSurfaceRightCylinder : public NgoGeoSurface, public NgoGeoSurfaceModule<NgoGeoSurfaceRightCylinder>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoSurfaceRightCylinder )

public :
   /*! @brief base constructor */
   NgoGeoSurfaceRightCylinder();
   /*! @brief Constructor
      \image html right_cylinder.png
      \image latex right_cylinder.png
   */
   /*! @param base base NgoGeoSurface surface */
   /*! @param length length (L)*/
   NgoGeoSurfaceRightCylinder(NgoGeoSurface & base, double length);

   /*! @brief copy constructor */
   NgoGeoSurfaceRightCylinder(const NgoGeoSurfaceRightCylinder & rhs)
   :NgoGeoSurface(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoSurfaceRightCylinder & operator=(const NgoGeoSurfaceRightCylinder & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoSurface::operator=(rhs);
           this->length = rhs.length;
           this->base   = rhs.base;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoSurfaceRightCylinder * clone() const { return new NgoGeoSurfaceRightCylinder(*this);};
   /*! method to set parameters from input arrays */
   /*! should be overloaded */
   virtual bool create(const double rp[], size_t nrp,
                        const int ip[], size_t nip,
                        const bool bp[], size_t nbp,
                        const char * tp[], size_t ntp
                        )
    {
        doCreate();
        this->length = rp[0];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

   /*! @brief method to access the NgoGeoSurface base surface of cylinder */
   NgoGeoSurface * getBaseSurface() {return (NgoGeoSurface *)base;};

   void setBaseSurface(NgoGeoSurface & base)
   {
       this->base = &base;
       surface.addDependency(base.perimeter);
       perimeter.addDependency(base.perimeter);
   }

protected:
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoSurfaceRightCylinder");
        registerVariableWithReference(vr_NgoGeoSurfaceRightCylinder_length,length);
        registerVariableWithReference(vr_NgoGeoSurfaceRightCylinder_lengthModule,length.module);
        associateMethodToVariable1(surface,NgoGeoSurfaceRightCylinder,doCalcSurface,length.modulated);
        associateMethodToVariable1(perimeter,NgoGeoSurfaceRightCylinder,doCalcPerimeter,length.modulated);

        registerPort(portLengthModule);
        portLengthModule.addVariable(length.module);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputePerimeter();

    // parameter variables
    public : modulatedParameterReal length;
    public : NgoSim::NgoPort portLengthModule;
   /*! @brief member defining base */
    public : NgoGeoSurface * base;
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
#define MODEL_IDENTIFIER NgoGeoSurfaceRightCylinder
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


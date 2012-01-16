#ifndef _NgoGeoSurfaceRectangle_h
#define _NgoGeoSurfaceRectangle_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceRectangle.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoSurface of a rectangle
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

const int vr_NgoGeoSurfaceRectangle_side1          = 0;
const int vr_NgoGeoSurfaceRectangle_side2          = 1;
const int vr_NgoGeoSurfaceRectangle_side1Module    = 100;
const int vr_NgoGeoSurfaceRectangle_side2Module    = 101;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register an rectangle surface
It is a C wrapper to NgoGeo::NgoGeoSurfaceRectangle
@param side1 rectangle first side length
@param side2 rectangle second side length
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGO_GEO_EXPORT int NgoGeoSurfRegisterRectangle(double side1, double side2);

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
   CLASS NgoGeoSurfaceRectangle DECLARATION
*******************************************************************************/
/*!
@class NgoGeoSurfaceRectangle
@brief class NgoGeoSurface to compute surface and perimeter of a rectangle
\image html rectangle.png
\image latex rectangle.png
@ingroup GroupNgoGeoSurface
*/
class NGO_GEO_EXPORT NgoGeoSurfaceRectangle : public NgoGeoSurface, public NgoGeoSurfaceModule<NgoGeoSurfaceRectangle>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoSurfaceRectangle )

public :
   /*! @brief base constructor */
   NgoGeoSurfaceRectangle();
   /*! @brief Constructor
      \image html rectangle.png
      \image latex rectangle.png
   */
   /*! @param side1 first side of rectangle (a)*/
   /*! @param side2 second side of rectangle (b) */
   NgoGeoSurfaceRectangle(double side1, double side2);
   /*! @brief copy constructor */
   NgoGeoSurfaceRectangle(const NgoGeoSurfaceRectangle & rhs)
   :NgoGeoSurface(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoSurfaceRectangle & operator=(const NgoGeoSurfaceRectangle & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoSurface::operator=(rhs);
           this->side1 = rhs.side1;
           this->side2 = rhs.side2;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoSurfaceRectangle * clone() const { return new NgoGeoSurfaceRectangle(*this);};
   /*! method to set parameters from input arrays */
   /*! should be overloaded */
   virtual bool create(const double rp[], size_t nrp,
                        const int ip[], size_t nip,
                        const bool bp[], size_t nbp,
                        const char * tp[], size_t ntp
                        )
    {
        doCreate();
        side1 = rp[0];
        side2 = rp[1];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

protected:
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoSurfaceRectangle");
        registerVariableWithReference(vr_NgoGeoSurfaceRectangle_side1,side1);
        registerVariableWithReference(vr_NgoGeoSurfaceRectangle_side2,side2);
        registerVariableWithReference(vr_NgoGeoSurfaceRectangle_side1Module,side1.module);
        registerVariableWithReference(vr_NgoGeoSurfaceRectangle_side2Module,side2.module);
        associateMethodToVariable2(surface,NgoGeoSurfaceRectangle,doCalcSurface,side1.modulated,side2.modulated);
        associateMethodToVariable2(perimeter,NgoGeoSurfaceRectangle,doCalcPerimeter,side1.modulated,side2.modulated);

        registerPort(portSide1Module);
        portSide1Module.addVariable(side1.module);
        registerPort(portSide2Module);
        portSide2Module.addVariable(side2.module);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputePerimeter();

    // parameter variables
    public : modulatedParameterReal side1, side2;
    public : NgoSim::NgoPort portSide1Module, portSide2Module;
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
#define MODEL_IDENTIFIER NgoGeoSurfaceRectangle
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


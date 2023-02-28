#ifndef _NgoGeoSurfaceTriangle_h
#define _NgoGeoSurfaceTriangle_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceTriangle.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoSurfaceTriangle
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

const int vr_NgoGeoSurfaceTriangle_side1          = 0;
const int vr_NgoGeoSurfaceTriangle_side2          = 1;
const int vr_NgoGeoSurfaceTriangle_side3          = 2;
const int vr_NgoGeoSurfaceTriangle_side1Module    = 100;
const int vr_NgoGeoSurfaceTriangle_side2Module    = 101;
const int vr_NgoGeoSurfaceTriangle_side3Module    = 102;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a triangle surface
It is a C wrapper to NgoGeo::NgoGeoSurfaceTriangle
@param side1 triangle first side length
@param side2 triangle second side length
@param side3 triangle third side length
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGO_GEO_EXPORT int NgoGeoSurfRegisterTriangle(double side1, double side2, double side3);

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
   CLASS NgoGeoSurfaceTriangle DECLARATION
*******************************************************************************/
/*!
@class NgoGeoSurfaceTriangle
@brief class NgoGeoSurface to compute surface and perimeter of a triangle
\image html triangle.png
\image latex triangle.png
@ingroup GroupNgoGeoSurface
*/
class NGO_GEO_EXPORT NgoGeoSurfaceTriangle : public NgoGeoSurface, public NgoGeoSurfaceModule<NgoGeoSurfaceTriangle>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoSurfaceTriangle )

public :
   /*! @brief base constructor */
   NgoGeoSurfaceTriangle();
   /*! @brief Constructor
      \image html triangle.png
      \image latex triangle.png
   */
   /*! @param side1 first side of triangle (a)*/
   /*! @param side2 second side of triangle (b) */
   /*! @param side3 third side of triangle (c) */
   NgoGeoSurfaceTriangle(double side1, double side2, double side3);
   /*! @brief copy constructor */
   NgoGeoSurfaceTriangle(const NgoGeoSurfaceTriangle & rhs)
   :NgoGeoSurface(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoSurfaceTriangle & operator=(const NgoGeoSurfaceTriangle & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoSurface::operator=(rhs);
           this->side1 = rhs.side1;
           this->side2 = rhs.side2;
           this->side3 = rhs.side3;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoSurfaceTriangle * clone() const { return new NgoGeoSurfaceTriangle(*this);};
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
        side3 = rp[2];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

protected:
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoSurfaceTriangle");
        registerVariableWithReference(vr_NgoGeoSurfaceTriangle_side1,side1);
        registerVariableWithReference(vr_NgoGeoSurfaceTriangle_side2,side2);
        registerVariableWithReference(vr_NgoGeoSurfaceTriangle_side3,side3);
        associateMethodToVariable3(surface,NgoGeoSurfaceTriangle,doCalcSurface,side1.modulated,side2.modulated,side3.modulated);
        associateMethodToVariable3(perimeter,NgoGeoSurfaceTriangle,doCalcPerimeter,side1.modulated,side2.modulated,side3.modulated);

        registerPort(portSide1Module);
        portSide1Module.addVariable(side1.module);
        registerPort(portSide2Module);
        portSide2Module.addVariable(side2.module);
        registerPort(portSide3Module);
        portSide3Module.addVariable(side3.module);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputePerimeter();

    // parameter variables
    public : modulatedParameterReal side1, side2, side3;
    public : NgoSim::NgoPort portSide1Module, portSide2Module, portSide3Module;

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
#define MODEL_IDENTIFIER NgoGeoSurfaceTriangle
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


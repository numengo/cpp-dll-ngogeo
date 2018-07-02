#ifndef _NgoGeoSurfaceEllipse_h
#define _NgoGeoSurfaceEllipse_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfaceEllipse.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoSurface ellipse
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

const int vr_NgoGeoSurfaceEllipse_axis1          = 0;
const int vr_NgoGeoSurfaceEllipse_axis2          = 1;
const int vr_NgoGeoSurfaceEllipse_axis1Module    = 100;
const int vr_NgoGeoSurfaceEllipse_axis2Module    = 101;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register an ellipse surface
It is a C wrapper to NgoGeo::NgoGeoSurfaceEllipse
@param axis1 ellipse first axis length
@param axis2 ellipse second axis length
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGOGEO_EXPORT int NgoGeoSurfRegisterEllipse(double axis1, double axis2);

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
   CLASS NgoGeoSurfaceEllipse DECLARATION
*******************************************************************************/
/*!
@class NgoGeoSurfaceEllipse
@brief class NgoGeoSurface to compute surface and perimeter of an ellipse
\image html ellipse.png
\image latex ellipse.png
@ingroup GroupNgoGeoSurface
*/
class NGOGEO_EXPORT NgoGeoSurfaceEllipse : public NgoGeoSurface, public NgoGeoSurfaceModule<NgoGeoSurfaceEllipse>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoSurfaceEllipse )

public :
   /*! @brief base constructor */
   NgoGeoSurfaceEllipse();
   /*! @brief Constructor
      \image html ellipse.png
      \image latex ellipse.png
   */
   /*! @param axis1 first axis of ellipse (a) */
   /*! @param axis2 second axis of ellipse  (b) */
   NgoGeoSurfaceEllipse(double axis1, double axis2);
   /*! @brief copy constructor */
   NgoGeoSurfaceEllipse(const NgoGeoSurfaceEllipse & rhs)
   :NgoGeoSurface(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoSurfaceEllipse & operator=(const NgoGeoSurfaceEllipse & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoSurface::operator=(rhs);
           this->axis1 = rhs.axis1;
           this->axis2 = rhs.axis2;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoSurfaceEllipse * clone() const { return new NgoGeoSurfaceEllipse(*this);};
   /*! method to set parameters from input arrays */
   /*! should be overloaded */
   virtual bool create(const double rp[], size_t nrp,
                        const int ip[], size_t nip,
                        const bool bp[], size_t nbp,
                        const char * tp[], size_t ntp
                        )
    {
        doCreate();
        axis1 = rp[0];
        axis2 = rp[1];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

protected:
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoSurfaceEllipse");
        registerVariableWithReference(vr_NgoGeoSurfaceEllipse_axis1,axis1);
        registerVariableWithReference(vr_NgoGeoSurfaceEllipse_axis2,axis2);
        registerVariableWithReference(vr_NgoGeoSurfaceEllipse_axis1Module,axis1.module);
        registerVariableWithReference(vr_NgoGeoSurfaceEllipse_axis2Module,axis2.module);
        associateMethodToVariable2(surface,NgoGeoSurfaceEllipse,doCalcSurface,axis1.modulated,axis2.modulated);
        associateMethodToVariable2(perimeter,NgoGeoSurfaceEllipse,doCalcPerimeter,axis1.modulated,axis2.modulated);

        registerPort(portAxis1Module);
        portAxis1Module.addVariable(axis1.module);
        registerPort(portAxis2Module);
        portAxis2Module.addVariable(axis2.module);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputePerimeter();

    // parameter variables
    public : modulatedParameterReal axis1, axis2;
    public : NgoSim::NgoPort portAxis1Module, portAxis2Module;
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
#define MODEL_IDENTIFIER NgoGeoSurfaceEllipse
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


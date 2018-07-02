#ifndef _NgoGeoSurfacePorousMatrixFiber_h
#define _NgoGeoSurfacePorousMatrixFiber_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurfacePorousMatrixFiber.h
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

const int vr_NgoGeoSurfacePorousMatrixFiber_Ac          = 0;
const int vr_NgoGeoSurfacePorousMatrixFiber_dw          = 1;
const int vr_NgoGeoSurfacePorousMatrixFiber_B           = 2;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a porous media surface for fiber matrixes
It is a C wrapper to NgoGeo::NgoGeoSurfacePorousMatrixFiber
@param surfind canister cross-section surface index
@param dw wire diameter
@param B porosity
@return surface index
@ingroup GroupNgoGeoWrapperCSurfAvl
*/
NGOGEO_EXPORT int NgoGeoSurfRegisterPorousMatrixFiber(int surfind, double dw, double B);

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
   CLASS NgoGeoSurfacePorousMatrixFiber DECLARATION
*******************************************************************************/
/*!
@class NgoGeoSurfacePorousMatrixFiber
@brief class NgoGeoSurface to compute surface and perimeter of a porous media surface for fiber matrixes
@ingroup GroupNgoGeoSurface
*/
class NGOGEO_EXPORT NgoGeoSurfacePorousMatrixFiber : public NgoGeoSurface, public NgoGeoSurfaceModule<NgoGeoSurfacePorousMatrixFiber>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoSurfacePorousMatrixFiber )

public :
   /*! @brief base constructor */
   NgoGeoSurfacePorousMatrixFiber();
   /*! @brief Constructor
    @param base canister cross-section surface object
    @param dw wire diameter
    @param B porosity */
   NgoGeoSurfacePorousMatrixFiber(NgoGeoSurface * base, double dw, double B);
   /*! @brief copy constructor */
   NgoGeoSurfacePorousMatrixFiber(const NgoGeoSurfacePorousMatrixFiber & rhs)
   :NgoGeoSurface(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoSurfacePorousMatrixFiber & operator=(const NgoGeoSurfacePorousMatrixFiber & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoSurface::operator=(rhs);
           setBaseSurface(*rhs.base_);
           this->dw_ = rhs.dw_;
           this->B_  = rhs.B_;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoSurfacePorousMatrixFiber * clone() const { return new NgoGeoSurfacePorousMatrixFiber(*this);};
   /*! method to set parameters from input arrays */
   /*! should be overloaded */
   virtual bool create(const double rp[], size_t nrp,
                        const int ip[], size_t nip,
                        const bool bp[], size_t nbp,
                        const char * tp[], size_t ntp
                        )
    {
        doCreate();
        base_ = getSurface(ip[0]);
        dw_ = rp[0];
        B_  = rp[1];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

   /*! @brief method to access the NgoGeoSurface base surface of cylinder */
   NgoGeoSurface * getBaseSurface() {return (NgoGeoSurface *)base_;};

   void setBaseSurface(NgoGeoSurface & base)
   {
       this->base_ = &base;
       surface.addDependency(base.surface);
       perimeter.addDependency(base.surface);
   }

protected:
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoSurfacePorousMatrixFiber");
        registerVariableWithReference(vr_NgoGeoSurfacePorousMatrixFiber_dw,dw_);
        registerVariableWithReference(vr_NgoGeoSurfacePorousMatrixFiber_B,B_);
        associateMethodToVariable1(surface,NgoGeoSurfacePorousMatrixFiber,doCalcSurface,B_);
        associateMethodToVariable2(perimeter,NgoGeoSurfacePorousMatrixFiber,doCalcPerimeter,B_,dw_);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputePerimeter();

    // parameter variables
    /*! @brief canister cross section area */
    NgoGeoSurface * base_;
    /*! @brief porosity */
    public : parameterReal B_;
    /*! @brief wire diameter */
    public : parameterReal dw_;
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
#define MODEL_IDENTIFIER NgoGeoSurfacePorousMatrixFiber
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


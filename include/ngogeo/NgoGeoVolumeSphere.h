#ifndef _NgoGeoVolumeSphere_h
#define _NgoGeoVolumeSphere_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolumeSphere.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoVolumeSphere
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

const int vr_NgoGeoVolumeSphere_diameter          = 0;
const int vr_NgoGeoVolumeSphere_diameterModule    = 100;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a volume with no specified geometry. It actually creates a sphere of equivalent volume using NgoGeo::NgoGeoVolumeSphere
@param vol volume value
@return volume index
@ingroup GroupNgoGeoWrapperCVolAvl
*/
NGO_GEO_EXPORT int NgoGeoVolRegister(double vol);

/*! @brief function to register a volume of a sphere
It is a C wrapper to NgoGeo::NgoGeoVolumeSphere
@param diam sphere diameter
@return volume index
@ingroup GroupNgoGeoWrapperCVolAvl
*/
NGO_GEO_EXPORT int NgoGeoVolRegisterSphere(double diam);

#ifdef __cplusplus
} // end extern "C"

/*******************************************************************************
   INCLUDES
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "ngogeo/NgoGeoVolume.h"

/*******************************************************************************
   DEFINES / TYPDEFS / ENUMS
*******************************************************************************/
namespace NgoGeo {

/*******************************************************************************
   CLASS NgoGeoVolumeSphere DECLARATION
*******************************************************************************/
/*!
@class NgoGeoVolumeSphere
@brief class NgoGeoVolume to compute surface and volume of a sphere
\image html sphere.png
\image latex sphere.png
@ingroup GroupNgoGeoVolume
*/
class NGO_GEO_EXPORT NgoGeoVolumeSphere : public NgoGeoVolume, public NgoGeoVolumeModule<NgoGeoVolumeSphere>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoVolumeSphere )

public :
   /*! @brief Base Constructor */
   NgoGeoVolumeSphere();

   /*! @brief Constructor
      \image html sphere.png
      \image latex sphere.png
   */
   /*! @param diam diameter of sphere (diam = 2 r)*/
   NgoGeoVolumeSphere(double diam);
   NgoGeoVolumeSphere(const NgoGeoVolumeSphere & rhs)
   :NgoGeoVolume(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoVolumeSphere & operator=(const NgoGeoVolumeSphere & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoVolume::operator=(rhs);
           this->diameter = rhs.diameter;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoVolumeSphere * clone() const { return new NgoGeoVolumeSphere(*this);};
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

protected :
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoVolumeSphere");
        registerVariableWithReference(vr_NgoGeoVolumeSphere_diameter,diameter);
        registerVariableWithReference(vr_NgoGeoVolumeSphere_diameterModule,diameter.module);

        associateMethodToVariable1(surface,NgoGeoVolumeSphere,doCalcSurface,diameter.modulated);
        associateMethodToVariable1(volume,NgoGeoVolumeSphere,doCalcVolume,diameter.modulated);

        registerPort(portDiameterModule);
        portDiameterModule.addVariable(diameter.module);
    }
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputeVolume();

    // parameter variables
    public : modulatedParameterReal diameter;
    public : NgoSim::NgoPort portDiameterModule;

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
#define MODEL_IDENTIFIER NgoGeoVolumeSphere
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


#ifndef _NgoGeoVolumeSpherePortion_h
#define _NgoGeoVolumeSpherePortion_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolumeSpherePortion.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoVolumeSpherePortion
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

const int vr_NgoGeoVolumeSpherePortion_diameter          = 0;
const int vr_NgoGeoVolumeSpherePortion_height            = 1;
const int vr_NgoGeoVolumeSpherePortion_diameterModule    = 100;
const int vr_NgoGeoVolumeSpherePortion_heightModule      = 101;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a volume of a sphere portion
It is a C wrapper to NgoGeo::NgoGeoVolumeSpherePortion
@param diam sphere diameter
@param height height of sphere portion
@return volume index
@ingroup GroupNgoGeoWrapperCVolAvl
*/
NGOGEO_EXPORT int NgoGeoVolRegisterSpherePortion(double diam, double height);


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
   CLASS NgoGeoVolumeSpherePortion DECLARATION
*******************************************************************************/
/*!
@class NgoGeoVolumeSpherePortion
@brief class NgoGeoVolume to compute surface and volume of a sphere portion
\image html sphere_portion.png
\image latex sphere_portion.png
@ingroup GroupNgoGeoVolume
*/
class NGOGEO_EXPORT NgoGeoVolumeSpherePortion : public NgoGeoVolume, public NgoGeoVolumeModule<NgoGeoVolumeSpherePortion>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoVolumeSpherePortion )

public :
   /*! @brief Base Constructor */
   NgoGeoVolumeSpherePortion();
   /*! @brief Constructor
      \image html sphere.png
      \image latex sphere.png
   */
   /*! @param diam diameter of sphere */
   /*! @param height height of sphere portion (h)*/
   NgoGeoVolumeSpherePortion(double diam, double height);
   /*! @brief copy constructor */
   NgoGeoVolumeSpherePortion(const NgoGeoVolumeSpherePortion & rhs)
   :NgoGeoVolume(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoVolumeSpherePortion & operator=(const NgoGeoVolumeSpherePortion & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoVolume::operator=(rhs);
           this->diameter = rhs.diameter;
           this->height   = rhs.height;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoVolumeSpherePortion * clone() const { return new NgoGeoVolumeSpherePortion(*this);};
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
        height   = rp[1];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);


protected :
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoVolumeSpherePortion");
        registerVariableWithReference(vr_NgoGeoVolumeSpherePortion_diameter      ,diameter      );
        registerVariableWithReference(vr_NgoGeoVolumeSpherePortion_height        ,height         );
        registerVariableWithReference(vr_NgoGeoVolumeSpherePortion_diameterModule,diameter.module);
        registerVariableWithReference(vr_NgoGeoVolumeSpherePortion_heightModule  ,height.module   );
        associateMethodToVariable2(surface,NgoGeoVolumeSpherePortion,doCalcSurface,diameter.modulated,height.modulated);
        associateMethodToVariable2(volume,NgoGeoVolumeSpherePortion,doCalcVolume,diameter.modulated,height.modulated);

        registerPort(portDiameterModule);
        portDiameterModule.addVariable(diameter.module);
        registerPort(portHeightModule);
        portHeightModule.addVariable(height.module);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputeVolume();

    // parameter variables
    public : modulatedParameterReal diameter, height;
    public : NgoSim::NgoPort portDiameterModule, portHeightModule;
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
#define MODEL_IDENTIFIER NgoGeoVolumeSpherePortion
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


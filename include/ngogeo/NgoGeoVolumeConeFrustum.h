#ifndef _NgoGeoVolumeConeFrustum_h
#define _NgoGeoVolumeConeFrustum_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolumeConeFrustum.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoVolumeConeFrustum
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

const int vr_NgoGeoVolumeConeFrustum_diameter1          = 0;
const int vr_NgoGeoVolumeConeFrustum_diameter2          = 1;
const int vr_NgoGeoVolumeConeFrustum_height             = 2;
const int vr_NgoGeoVolumeConeFrustum_diameter1Module    = 100;
const int vr_NgoGeoVolumeConeFrustum_diameter2Module    = 101;
const int vr_NgoGeoVolumeConeFrustum_heightModule       = 102;

#include "ngogeo/NgoGeoExports.h"

/*! @brief function to register a cone frustum volume
It is a C wrapper to NgoGeo::NgoGeoVolumeConeFrustum
@param diam1 base cone diameter
@param height  cylinder length
@param diam2 end diameter, (=0 for a cone)
@return volume index
@ingroup GroupNgoGeoWrapperCVolAvl
*/
NGOGEO_EXPORT int NgoGeoVolRegisterConeFrustum(double diam1, double height, double diam2);

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
   CLASS NgoGeoVolumeConeFrustum DECLARATION
*******************************************************************************/
/*!
@class NgoGeoVolumeConeFrustum
@brief class NgoGeoVolume to compute surface and volume of a cone frustum
\image html cone_frustum.png
\image latex cone_frustum.png
@ingroup GroupNgoGeoVolume
*/
class NGOGEO_EXPORT NgoGeoVolumeConeFrustum : public NgoGeoVolume, public NgoGeoVolumeModule<NgoGeoVolumeConeFrustum>
{
	DECLARE_DYNAMIC_CLASS_NGO( NgoGeoVolumeConeFrustum )

public :
   /*! @brief Base Constructor */
   NgoGeoVolumeConeFrustum();
   /*! @brief Constructor
      \image html cone_frustum.png
      \image latex cone_frustum.png
   */
   /*! @param diam1 first diameter of cone frustum (a) */
   /*! @param height of cone frustum (h) */
   /*! @param diam2  second diameter of cone frustum (b)*/
   NgoGeoVolumeConeFrustum(double diam1, double height, double diam2);
   /*! @brief copy constructor */
   NgoGeoVolumeConeFrustum(const NgoGeoVolumeConeFrustum & rhs)
   :NgoGeoVolume(rhs)
   {
       doCreate();
       *this = rhs;
   }
   /*! @brief operator = */
   NgoGeoVolumeConeFrustum & operator=(const NgoGeoVolumeConeFrustum & rhs)
   {
       if (this != &rhs)
       {
           NgoGeoVolume::operator=(rhs);
           this->diameter1 = rhs.diameter1;
           this->diameter2 = rhs.diameter2;
           this->height    = rhs.height;
       }
       return *this;
   }
   /*!@brief clone method */
   virtual NgoGeoVolumeConeFrustum * clone() const { return new NgoGeoVolumeConeFrustum(*this);};
   /*! method to set parameters from input arrays */
   /*! should be overloaded */
   virtual bool create(const double rp[], size_t nrp,
                        const int ip[], size_t nip,
                        const bool bp[], size_t nbp,
                        const char * tp[], size_t ntp
                        )
    {
        doCreate();
        diameter1 = rp[0];
        diameter2 = rp[1];
        height    = rp[2];
        return true;
    };

   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry);

protected :
    /*! @brief method to actually overload and define by user */
    virtual void doCreate()
    {
        setInstanceName("NgoGeoVolumeConeFrustum");
        registerVariableWithReference(vr_NgoGeoVolumeConeFrustum_diameter1      ,diameter1      );
        registerVariableWithReference(vr_NgoGeoVolumeConeFrustum_diameter2      ,diameter2      );
        registerVariableWithReference(vr_NgoGeoVolumeConeFrustum_height         ,height         );
        registerVariableWithReference(vr_NgoGeoVolumeConeFrustum_diameter1Module,diameter1.module);
        registerVariableWithReference(vr_NgoGeoVolumeConeFrustum_diameter2Module,diameter2.module);
        registerVariableWithReference(vr_NgoGeoVolumeConeFrustum_heightModule   ,height.module   );
        associateMethodToVariable3(surface,NgoGeoVolumeConeFrustum,doCalcSurface,diameter1.modulated,diameter2.modulated,height.modulated);
        associateMethodToVariable3(volume,NgoGeoVolumeConeFrustum,doCalcVolume,diameter1.modulated,diameter2.modulated,height.modulated);

        registerPort(portDiameter1Module);
        portDiameter1Module.addVariable(diameter1.module);
        registerPort(portDiameter2Module);
        portDiameter2Module.addVariable(diameter2.module);
        registerPort(portHeightModule);
        portHeightModule.addVariable(height.module);
    };
    /*! @brief virtual method to actually compute surface */
    virtual double doComputeSurface();
    /*! @brief virtual method to actually compute perimeter */
    virtual double doComputeVolume();

    // parameter variables
    public : modulatedParameterReal diameter1, diameter2, height;
    public : NgoSim::NgoPort portDiameter1Module, portDiameter2Module, portHeightModule;
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
#define MODEL_IDENTIFIER NgoGeoVolumeConeFrustum
#define MODEL_GUID
#include "ngosim/NgoFmi.h"

#endif


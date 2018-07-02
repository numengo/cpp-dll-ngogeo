#ifndef _NgoGeoVolume_h
#define _NgoGeoVolume_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoVolume.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoVolume
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
const int vr_NgoGeoVolume_surface          = 200;
const int vr_NgoGeoVolume_volume           = 201;
const int vr_NgoGeoVolume_volumeIndex      = 202;

#ifdef __cplusplus
} // end extern "C"

/*******************************************************************************
   INCLUDES
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "ngogeo/NgoGeoGeometry.h"
#include "ngocommon/NgoObjectManager.h"

/*******************************************************************************
   DEFINES / TYPDEFS / ENUMS
*******************************************************************************/
namespace NgoGeo {

/*******************************************************************************
   CLASS NgoGeoVolume DECLARATION
*******************************************************************************/
/*! @defgroup GroupNgoGeoVolume Geometry Volume Utilities
@ingroup GroupNgoGeoGeometry
*/
/*!
@class NgoGeoVolume
@brief Abstract class for a NgoGeoVolume
@ingroup GroupNgoGeoVolume
*/
class NGOGEO_EXPORT NgoGeoVolume : public NgoGeoGeometry
{
	DECLARE_ABSTRACT_CLASS_NGO( NgoGeoVolume )

public :
   /*! @brief Base Constructor */
   NgoGeoVolume();
   /*! @brief Destructor */
   virtual ~NgoGeoVolume();
   /*! @brief copy constructor */
   NgoGeoVolume(const NgoGeoVolume & rhs);
   /*! @brief operator = */
   NgoGeoVolume & operator=(const NgoGeoVolume & rhs);
   /*! @brief clone method */
   virtual NgoGeoVolume * clone() const = 0;
   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry)=0;

   /*! @brief method to compute volume */
   double computeVolume() { volume.update(); return volume(); };
   /*! @brief method to compute surface */
   double computeSurface() { surface.update(); return surface(); };

protected :
    /*! @brief method to actually overload and define by user */
    virtual void doCreate();
    /*! @brief method to actually overload and define by user */
    virtual void doCalcMain() {doCalcVolume();};
   /*! @brief virtual method to actually compute surface */
   virtual double doComputeSurface() = 0;
   /*! @brief virtual method to actually compute volume */
   virtual double doComputeVolume() = 0;

   /*! @brief virtual method to actually compute suerface */
   void doCalcSurface() { surface = pow(fabs(mainModule() ),2./3.) *  doComputeSurface(); };
   /*! @brief virtual method to actually compute volume */
   void doCalcVolume() { volume = mainModule() * doComputeVolume(); };

public :
   /*! output surface and volume */
   outputVariableReal surface, volume;
   /*! output surface index */
   outputVariableInteger volumeIndex;
   /*! port to connect volume instance, with only input volumeIndex */
   NgoSim::NgoPort portVolume;

};

/*! @brief method to retrieve surfaces vector and use indexes */
NGOGEO_EXPORT std::vector<NgoGeo::NgoGeoVolume *> & getVolumes();
/*! @brief method to retrieve volume with its index */
NGOGEO_EXPORT NgoGeo::NgoGeoVolume * getVolume(const variableInteger & index);
/*! @brief method to retrieve volume with its index */
NGOGEO_EXPORT NgoGeo::NgoGeoVolume * getVolume(const int index);

} // namespace NgoGeo

/*******************************************************************************
   MODULES, MANAGERS, REGISTRANT, etc...
********************************************************************************/

typedef NgoGeo::NgoGeoVolume * (CreateVolume)(NgoObj::NgoComponent &);

 /*! @class NgoGeoVolumeManager
@brief this is a class to manage NgoGeoVolume objects
@ingroup GroupNgoObjectManagersAvl */
//typedef NgoObjectManager<NgoGeo::NgoGeoVolume,CreateVolume> NgoGeoVolumeManager;
//class NGOGEO_EXPORT NgoGeoVolumeManager : public NgoObjectManager<NgoGeo::NgoGeoVolume,CreateVolume> {};
class NGOGEO_EXPORT NgoGeoVolumeManager : public NgoObjectManagerBase<NgoGeo::NgoGeoVolume,CreateVolume> , public NgoSingleton< NgoGeoVolumeManager >
{
   friend class NgoSingleton< NgoGeoVolumeManager >;
public :
   NgoGeo::NgoGeoVolume * create(NgoObj::NgoComponent & surface, const char * i_label=0L);
};

namespace NgoGeo {

 /*! @brief NgoGeoVolumeRegistrant objects registration .
Use this class to register your new object with the object manager.
All you have to do is instantiate an NgoGeoVolumeRegistrant object.
@par
Example code to use in one of your object source files (supposedly called "MyObject"):
@code
namespace
{
    NgoGeoVolumeRegistrant<MyObject> registration;
}
@endcode
@ingroup GroupNgoObjectManagersAvlComp
*/
	template<class S> class NgoGeoVolumeRegistrant : public NgoSim::NgoComponentRegistrant<S>
{
public:
    /*! @brief Base constructor */
    NgoGeoVolumeRegistrant()
    {
       NgoGeoVolumeManager::get()->registerObject(&createObject,&freeObject,NgoObjectModule<S>::getName(),NgoObjectModule<S>::getDescription(),NgoObjectModule<S>::getType(),NgoObjectModule<S>::getXsiType(),NgoObjectModule<S>::getXsd());
    }
    /*! @brief  constructor using prototype to register in manager */
    static NgoGeoVolume * createObject(NgoObj::NgoComponent & component)
    {
        NgoGeoVolume * object = new S();
        object->create(component);
        return object;
    }

    /*! @brief Function for freeing the object */
    /*! @param object the object to free */
    static void freeObject( NgoGeoVolume * object)
    { delete object; }
};

 /*! @brief define macros for registering an object
Simply use this macro to register your object (supposed NgoObject) by using
REGISTER_VOLUME(NGO_OBJECT)
@note the macro will only work if you register one object per cpp
@ingroup GroupNgoObjectManagersAvlComp
*/
#define REGISTER_VOLUME(OBJECT) \
namespace { NgoGeoVolumeRegistrant<OBJECT> registration; } \

} // namespace NgoGeo

template< typename T > class NgoGeoVolumeModule : public NgoObjectModule<T>
{};

#define DESCRIPTION_VOLUME(OBJECT,DESC,XSITYPE) \
template<> std::string NgoObjectModule<OBJECT>::name = stringize(MODEL_IDENTIFIER); \
template<> std::string NgoObjectModule<OBJECT>::type = #OBJECT; \
template<> std::string NgoObjectModule<OBJECT>::description = DESC; \
template<> std::string NgoObjectModule<OBJECT>::xsitype = XSITYPE; \
template<> std::string NgoObjectModule<OBJECT>::xsd = "TemplateGeometry.xsd"; \
template<> std::string NgoObjectModule<OBJECT>::guid = stringize(GUID); \
template<> std::vector<OBJECT *> NgoObjectModule<OBJECT>::instances(0,0L); \
const char * ngoGetInstanceName() { return NgoObjectModule<OBJECT>::getName();}

#endif // end of ifdef __cplusplus

#endif


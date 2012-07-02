#ifndef _NgoGeoSurface_h
#define _NgoGeoSurface_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoSurface.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoSurface
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

const int vr_NgoGeoSurface_surface          = 200;
const int vr_NgoGeoSurface_perimeter        = 201;
const int vr_NgoGeoSurface_hydraulicDiameter= 202;
const int vr_NgoGeoSurface_surfaceIndex     = 203;

#include "ngogeo/NgoGeoExports.h"

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
   CLASS NgoGeoSurface DECLARATION
*******************************************************************************/
/*! @defgroup GroupNgoGeoSurface Geometry Surface Utilities
@ingroup GroupNgoGeoGeometry
*/
/*!
@class NgoGeoSurface
@brief Abstract class for a NgoGeoSurface
@ingroup GroupNgoGeoSurface
*/
class NGO_GEO_EXPORT NgoGeoSurface : public NgoGeoGeometry
{
	DECLARE_ABSTRACT_CLASS_NGO( NgoGeoSurface )

public :
   /*! @brief Base Constructor */
   NgoGeoSurface();
   /*! @brief destructor */
   virtual ~NgoGeoSurface();
   /*! @brief copy constructor */
   NgoGeoSurface(const NgoGeoSurface & rhs);
   /*! @brief operator = */
   NgoGeoSurface & operator=(const NgoGeoSurface & rhs);
   /*! @brief clone method */
   virtual NgoGeoSurface * clone() const = 0;
   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry)=0;

   /*! @brief method to compute surface */
   double computeSurface() {
       surface.update();
       return surface();
    };
   /*! @brief method to compute perimeter */
   double computePerimeter() {
       perimeter.update();
       return perimeter();
   };
   /*! @brief method to compute hydraulic diameter (4 * surface / perimeter) */
   double computeHydraulicDiameter()
   {
       hydraulicDiameter.update();
       return hydraulicDiameter();
   };

   /*! @brief method to set user defined hydraulic diameter */
   /*! Note that it will be added as a geometric parameter and thus can
   be modulated using methods setModule() and setModulatedParameter()
   /*! @param diam hydraulic diameter */
   void setHydraulicDiameter(double diam)
   {
      hydraulicDiameter = diam;
      if (!isHydDiamUserDef())
          isHydDiamUserDef = true;
   };

protected :
    /*! @brief method to actually overload and define by user */
    virtual void doCreate();
    /*! @brief method to actually overload and define by user */
    virtual void doCalcMain() {doCalcSurface();};
   /*! @brief virtual method to actually compute surface */
   virtual double doComputeSurface() = 0;
   /*! @brief virtual method to actually compute perimeter */
   virtual double doComputePerimeter() = 0;

   /*! @brief virtual method to actually compute hydraulic diameter */
   void doCalcHydraulicDiameter()
   {
      if (isHydDiamUserDef())
         hydraulicDiameter = sqrt(fabs(mainModule() )) * hydraulicDiameter.modulated();
	  else 
	  {
		  surface.update();
		  perimeter.update();
	      hydraulicDiameter = 4. * surface() / perimeter();
	  }
   };
   /*! @brief virtual method to actually compute suerface */
   void doCalcSurface() { surface = mainModule() * doComputeSurface(); };
   /*! @brief virtual method to actually compute perimeter */
   void doCalcPerimeter() { perimeter = sqrt(fabs(mainModule() )) * doComputePerimeter();};

   /*! @brief boolean to know if hydraulic diameter has been set by user */
   variableBoolean isHydDiamUserDef;

public :
    /*! @brief hydraulic diameter */
   modulatedParameterReal hydraulicDiameter;
   /*! output surface and perimeter */
   outputVariableReal surface, perimeter;
   /*! output surface index */
   outputVariableInteger surfaceIndex;
   /*! port to connect surface instance, with only input surfaceIndex */
   NgoSim::NgoPort portSurface;
};

/*! @brief method to retrieve surfaces vector and use indexes */
NGO_GEO_EXPORT std::vector<NgoGeo::NgoGeoSurface *> & getSurfaces();
/*! @brief method to retrieve surface with its index */
NGO_GEO_EXPORT NgoGeo::NgoGeoSurface * getSurface(const variableInteger & index);
/*! @brief method to retrieve surface with its index */
NGO_GEO_EXPORT NgoGeo::NgoGeoSurface * getSurface(const int index);

} // namespace NgoGeo

/*******************************************************************************
   MODULES, MANAGERS, REGISTRANT, etc...
********************************************************************************/

typedef NgoGeo::NgoGeoSurface * (CreateSurface)(NgoObj::NgoComponent &);

 /*! @class NgoGeoSurfaceManager
@brief this is a class to manage NgoGeoSurface objects
@ingroup GroupNgoObjectManagersAvl */
//typedef NgoObjectManager<NgoGeo::NgoGeoSurface,CreateSurface> NgoGeoSurfaceManager;
//class NGO_GEO_EXPORT NgoGeoSurfaceManager : public NgoObjectManager<NgoGeo::NgoGeoSurface,CreateSurface> {};

//class NGO_GEO_EXPORT NgoGeoSurfaceManager : public NgoObjectManagerBase<NgoGeo::NgoGeoSurface,CreateSurface> , public NgoSingleton< NgoGeoSurfaceManager >
class NGO_GEO_EXPORT NgoGeoSurfaceManager : public NgoObjectManagerBase<NgoGeo::NgoGeoSurface,CreateSurface> , public NgoSingleton< NgoGeoSurfaceManager >
{
   friend class NgoSingleton< NgoGeoSurfaceManager >;
public :
   NgoGeo::NgoGeoSurface * create(NgoObj::NgoComponent & surface, const char * i_label=0L);
};

namespace NgoGeo {
 /*! @brief NgoGeoSurfaceRegistrant objects registration .
Use this class to register your new object with the object manager.
All you have to do is instantiate an NgoGeoSurfaceRegistrant object.
@par
Example code to use in one of your object source files (supposedly called "MyObject"):
@code
namespace
{
    NgoGeoSurfaceRegistrant<MyObject> registration;
}
@endcode
@ingroup GroupNgoObjectManagersAvlComp
*/
	template<class S> class NgoGeoSurfaceRegistrant : public NgoSim::NgoComponentRegistrant<S>
{
public:
    /*! @brief Base constructor */
    NgoGeoSurfaceRegistrant()
    {
       NgoGeoSurfaceManager::get()->registerObject(&createObject,&freeObject,NgoObjectModule<S>::getName(),NgoObjectModule<S>::getDescription(),NgoObjectModule<S>::getType(),NgoObjectModule<S>::getXsiType(),NgoObjectModule<S>::getXsd());
    }
    /*! @brief  constructor using prototype to register in manager */
    static NgoGeoSurface * createObject(NgoObj::NgoComponent & component)
    {
        NgoGeoSurface * object = new S();
        object->create(component);
        return object;
    }

    /*! @brief Function for freeing the object */
    /*! @param object the object to free */
    static void freeObject( NgoGeoSurface * object)
    { delete object; }
};

 /*! @brief define macros for registering an object
Simply use this macro to register your object (supposed NgoObject) by using
REGISTER_SURFACE(NGO_OBJECT)
@note the macro will only work if you register one object per cpp
@ingroup GroupNgoObjectManagersAvlComp
*/
#define REGISTER_SURFACE(OBJECT) \
namespace { NgoGeoSurfaceRegistrant<OBJECT> registration; };

} // namespace NgoGeo

template< typename T > class NgoGeoSurfaceModule : public NgoObjectModule<T>
{};

#define DESCRIPTION_SURFACE(OBJECT,DESC,XSITYPE) \
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


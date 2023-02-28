#ifndef _NgoGeoGeometry_h
#define _NgoGeoGeometry_h
/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoGeometry.h
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing definition of a class for a NgoGeoGeometry

http://membres.lycos.fr/piquard/geomatri.html
http://www.webmaths.com/rechercher/geometrie.php3
http://www.webmaths.com/rechercher/aires_volumes.htm
http://pagesperso-orange.fr/daniel.robert9/Formulaires_mathematiques.html
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

const unsigned int vr_NgoGeometry_mainModule = 99; // 100-1 : // for the overall module

#ifdef __cplusplus
} // end extern "C"


/*******************************************************************************
   INCLUDES
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "ngoobj/NgoObject.h"
#include "ngoobj/NgoVariableGroup.h"
#include "ngoobj/NgoValidity.h"

#include "ngosim/NgoComponent.h"

#include "math.h"

#include "ngoerr/NgoError.h"

#include "ngogeo/NgoGeoExports.h"

#define CATCH_GEO(FUNCTION) \
   catch (NgoError & er) \
   { \
      er.addScopeError(FUNCTION); \
      NgoProcessError(er); \
   } \
   catch (...) \
   { NgoProcessError(NgoErrorUnknown("Unknown error",FUNCTION,"numenGo|Geo")); }\


/*******************************************************************************
   DEFINES / TYPDEFS / ENUMS
*******************************************************************************/
namespace NgoGeo {

static std::vector<std::string> vstring_empty;

static double d_pi = 3.141592653589793;

class modulatedParameterReal : public parameterReal
{
    DECLARE_DYNAMIC_TEMPLATE_CLASS_NGO(NGO_GEO_EXPORT,modulatedParameterReal)

public:
    /*! @brief base constructor */
    modulatedParameterReal(const Real value = 0.)
    :parameterReal(value),module(1.)
    { associateMethodToVariable2(modulated,modulatedParameterReal,doCalcModulated,module,*this); }
    /*! @brief base constructor */
    modulatedParameterReal(const std::vector<Real> &value)
    :parameterReal(value)
    { associateMethodToVariable2(modulated,modulatedParameterReal,doCalcModulated,module,*this); }
    modulatedParameterReal(const variable<Real> &value)
    :parameterReal(value)
    { associateMethodToVariable2(modulated,modulatedParameterReal,doCalcModulated,module,*this); }
    /*! @brief copy constructor */
    modulatedParameterReal(const modulatedParameterReal & rhs)
    :parameterReal(rhs),module(rhs.module)
    { associateMethodToVariable2(modulated,modulatedParameterReal,doCalcModulated,module,*this); }
    /*! @brief operator = */
    virtual modulatedParameterReal & operator= (const Real &rhs)
    {   this->parameterReal::operator=(rhs);
        module = 1;
        return *this;
    };    /*! @brief operator = */
    virtual modulatedParameterReal & operator= (const std::vector<Real> &rhs)
    {   this->parameterReal::operator=(rhs);
        module = 1;
        return *this;
    };
    /*! @brief operator = */
    virtual modulatedParameterReal & operator= (const variable<Real> &rhs)
    {   this->parameterReal::operator=(rhs);
        module = 1;
        return *this;
    };
    virtual modulatedParameterReal & operator= (const modulatedParameterReal & rhs)
    {   this->parameterReal::operator=(rhs);
        module = rhs.module;
        return *this;
    };

    inputVariableReal module;
    outputVariableReal modulated;
protected:
    void doCalcModulated() {modulated = module() * (*this)();}
};

/*******************************************************************************
   CLASS NgoGeoGeometry DECLARATION
*******************************************************************************/
/*! @defgroup GroupNgoGeoGeometry GEO modules
@ingroup GroupNgoUtils
*/
/*!
@class NgoGeoGeometry
@brief Abstract class for a NgoGeoGeometry
@ingroup GroupNgoGeoGeometry
*/
class NGO_GEO_EXPORT NgoGeoGeometry : public NgoSim::NgoComponent
{
	DECLARE_ABSTRACT_CLASS_NGO( NgoGeoGeometry )

public :
    /*! @brief Base Constructor */
    NgoGeoGeometry();
    /*! @brief virtual destructor */
    virtual ~NgoGeoGeometry() {};
    /*! @brief copy constructor */
    NgoGeoGeometry(const NgoGeoGeometry & rhs);
    /*! @brief operator = */
//    virtual NgoGeoGeometry & operator=(const NgoGeoGeometry & rhs){return *this;};
    /*! @brief clone method */
    virtual NgoGeoGeometry * clone() const = 0;
   /*! @brief method to create a geometry from a NgoObj::NgoVariableGroup that contains all variables */
   /*! @param geometry NgoObj::NgoVariableGroup object containing all variables */
   virtual bool create(NgoObj::NgoComponent & geometry) = 0;

   /*! @brief method to set a modulated parameter that will be modulated by NgoGeoGeometry::setModule method*/
   /*! @param pname dimension identifier */
   void setModulatedParameter(const char * pname);
   /*! @brief method to set a modulated parameter that will be modulated by NgoGeoGeometry::setModule method*/
   /*! @param pname dimension identifier */
   /*! @param module module of dimension */
   void setModule(double module, const char * pname);
   /*! @brief Destructor */
   void setModule(double module)
    {
        if (modulatedParameter_)
            modulatedParameter_->module = module;
        else
            mainModule = module;
    };

   /*! @brief method to set overall surface module */
   /*! @param module value to set */
   void setOverallModule(double module) { this->mainModule = module; }
   /*! @brief method to get overall surface module */
   double getOverallModule() const {return this->mainModule();}

protected:
    /*! @brief only doCreate and doCalcMain are to be updated */
    /*! @brief method to actually overload and define by user */
    virtual void doCreate() = 0;
    /*! @brief method to actually initialize the component */
    virtual void doInit() {};
    /*! @brief method actually initialize the component from inputs */
    virtual void doInitializeFromInputs() {};
    /*! @brief method to actually overload and define by user */
    virtual void doCalcMain() = 0;
    /*! @brief method to update the model after an event */
    virtual void doEventUpdate() {};
    /*! @brief method to actually overload and define by user to know if event update is to be called */
    virtual bool doCallEventUpdate() { return false;};
    /*! @brief method to actually calculate event indicators */
    virtual void doCalcEventIndicators() {};

public :
// ports
    NgoSim::NgoPort portMainModule;
// variables
   /*! @brief overall module, set to 1 by default */
    inputVariableReal mainModule;

protected:
    /*! pointer to modulated parameter */
    modulatedParameterReal * modulatedParameter_;
};

} // namespace NgoGeo

#endif // end of ifdef __cplusplus

#endif


/*******************************************************************************
   FILE DESCRIPTION
*******************************************************************************/
/*!
@file NgoGeoGeometry.cpp
@author Cedric ROMAN - roman@numengo.com
@date May 2009
@brief File containing generic classes  member definitions for a @ref PageNgoGeoGeometryDef "Geometry".
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
   DOXYGEN GROUP DEFINION
*******************************************************************************/


/*******************************************************************************
   INCLUDES
*******************************************************************************/
#include <math.h>
#include <iostream>
#include <sstream>
#include "ngogeo/NgoGeoGeometry.h"


namespace NgoGeo {

using namespace NgoSim;

IMPLEMENT_DYNAMIC_CLASS_NGO( modulatedParameterReal , parameterReal )

/*******************************************************************************
   CLASS NgoGeoGeometry DEFINITION
*******************************************************************************/
IMPLEMENT_ABSTRACT_CLASS_NGO(NgoGeoGeometry, NgoSim::NgoComponent)

NgoGeoGeometry::NgoGeoGeometry()
:NgoComponent(),mainModule(1.),modulatedParameter_(0L)
{
    registerVariableWithReference(vr_NgoGeometry_mainModule,mainModule);
    registerPort(portMainModule);
    portMainModule.addVariable(mainModule);
}

NgoGeoGeometry::NgoGeoGeometry(const NgoGeoGeometry & rhs)
:NgoComponent(rhs),mainModule(rhs.mainModule),modulatedParameter_(0L)
{
    registerVariableWithReference(vr_NgoGeometry_mainModule,mainModule);
    registerPort(portMainModule);
    portMainModule.addVariable(mainModule);
}


void NgoGeoGeometry::setModule(double module,const char * pname)
{
    std::vector<variableBase *> vars= findVariableByName(pname);
    if (!vars.size())
    {
       std::ostringstream oss;
       oss << "Impossible to find parameter called : " << pname << " in available parameters." << std::endl;
       std::string msg = oss.str();
       throw NgoErrorInvalidArgument(2,msg,"NgoGeoGeometry::setModule","numenGo|Geo");
    }
    for (unsigned i=0;i<vars.size();i++)
    {
        modulatedParameterReal * var = dynamic_cast<modulatedParameterReal *>(vars[i]);
        if (var)
            var->module = module;
    }
    setModulatedParameter(pname);
}

void NgoGeoGeometry::setModulatedParameter(const char * pname)
{
   std::vector<variableBase *> vars= findVariableByName(pname);
   if (!vars.size()==1)
   {
         std::ostringstream oss;
         oss << "Impossible to find one parameter called : " << pname << " in available parameters." << std::endl;
         std::string msg = oss.str();
         throw NgoErrorInvalidArgument(1,msg,"NgoGeoGeometry::setModulatedParameter","numenGo|Geo");
   }
   modulatedParameter_ = dynamic_cast<modulatedParameterReal *>(vars[0]);;
}

} // namespace NgoGeo

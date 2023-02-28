dofile (path.join(os.getenv("DIR_SCRIPTS_ROOT"),"premake5_common.lua"))

workspace "NgoGeo"

    SolutionConfiguration()
    defines {
                "NGO_ERR_USE_DYN"
               ,"MU_PSR_USE_DYN"
               ,"NGO_COM_USE_DYN"
               ,"XMLMGR_USE_DYNAMIC"
               ,"NGO_UNIT_USE_DYN"
               ,"NGO_OBJ_USE_DYN"
               ,"NGO_SIM_USE_DYN"
               ,"NGO_GEO_USE_DYN"
    }
    local _exportSymbol = "NGO_GEO_MAKE_DLL"
    links { 
               "NgoErr"
               ,"muParser"
               ,"NgoCommon"
               ,"NgoXmlMgr"
               ,"NgoUnit"
               ,"NgoObj"
               ,"NgoXml"
               ,"NgoSim"
    }
    
    -- PROTECTED REGION ID(NgoGeo.premake.solution) ENABLED START
	configuration {"vs2010"}
			links {"NgoLibxml2"}
	configuration {"linux"}
			links {"xml2"}

    -- PROTECTED REGION END


project "NgoGeo"

    PrefilterSharedLibBuildOptions("NgoGeo")
    defines {_exportSymbol}
    
    -- PROTECTED REGION ID(NgoGeo.premake.sharedlib) ENABLED START

    -- PROTECTED REGION END

    FilterSharedLibBuildOptions("NgoGeo")


project "test_NgoGeo"

    PrefilterTestBuildOptions("test_NgoGeo")
    links { "NgoGeo"}
    
    -- PROTECTED REGION ID(NgoGeo.premake.test) ENABLED START
    links { "NgoErr" }

    -- PROTECTED REGION END

    FilterTestBuildOptions("test_NgoGeo")

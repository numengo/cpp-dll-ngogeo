
dofile (path.join(os.getenv("DIR_SCRIPTS_ROOT"),"premake5_common.lua"))

workspace "NgoGeo" 

    SolutionConfiguration()
    defines {
        "NGOLIBXML2_USE_DYN",
        "NGOERR_USE_DYN",
        "MU_PSR_USE_DYN",
        "NGOCOM_USE_DYN",
        "XMLMGR_USE_DYN",
        "NGOUNIT_USE_DYN",
        "NGOOBJ_USE_DYN",
        "NGOXML_USE_DYN",
        "NGOSIM_USE_DYN",
        "NGOGEO_USE_DYN"
    }
    local _exportSymbol = "NGOGEO_MAKE_DLL"
    links { 
        "NgoLibxml2",
        "NgoErr",
        "muParser",
        "NgoCommon",
        "NgoXmlMgr",
        "NgoUnit",
        "NgoObj",
        "NgoXml",
        "NgoSim"
    }
    
    -- PROTECTED REGION ID(NgoGeo.premake.solution) ENABLED START
    -- Insert here user code

    -- End of user code
    -- PROTECTED REGION END

project "NgoGeo"

    PrefilterSharedLibBuildOptions("NgoGeo")
    defines {_exportSymbol}
    
   -- PROTECTED REGION ID(NgoGeo.premake.sharedlib) ENABLED START
   -- Insert here user code

   -- End of user code
   -- PROTECTED REGION END

    FilterSharedLibBuildOptions("NgoGeo")


    


dofile (path.join(os.getenv("DirScriptsRoot"),"premake_common.lua"))

-- solution NgoGeo --
solution "NgoGeo"

    SolutionConfiguration()

    -- COMMON CONFIGURATION MODIFICATION - START --
    configuration {}
        -- common defines (adapt if necessary) --
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
       -- for shared libs, export statement
       local _exportSymbol = "NGO_GEO_MAKE_DLL"
       -- suffix to use for library versionning
       local _version = ""
       -- common libs  --
       links { 
                "NgoLibxml2"
               ,"NgoErr"
               ,"muParser"
               ,"NgoCommon"
               ,"NgoXmlMgr"
               ,"NgoUnit"
               ,"NgoObj"
               ,"NgoXml"
               ,"NgoSim"
          }
    -- COMMON CONFIGURATION MODIFICATION - END --

project "NgoGeo"
    -- PROJECT MODIFICATIONS START--
    local _targetname = "NgoGeo"
    -- additional defines --
    defines {_exportSymbol}
    -- PROJECT MODIFICATIONS END--

    AppendSharedLibBuildOptions(_targetname.._version)

project "test_NgoGeo"
    -- PROJECT MODIFICATIONS START--
    local _targetname = "test_NgoGeo"
    links {"NgoGeo"}
    -- PROJECT MODIFICATIONS END--

    AppendTestBuildOptions(_targetname.._version)

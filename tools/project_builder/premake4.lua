--Name
local name = "InstancedCulling"

--Directory stuff
local cwd = os.getcwd() .. "/"
local project_location_rel = "../../"
local root_location_rel = "../../"
local build_location_rel =   project_location_rel .. "build/"                  -- Build
local source_location_rel =  project_location_rel .. "src/"                    -- Source
local data_location_rel = project_location_rel .. "data/"		               -- Data
local headers_location_rel = root_location_rel .. "externals/headers/"         -- Headers
local libs_location_rel =    root_location_rel .. "externals/libs/"            -- Libraries

--glew
local lib_glew = libs_location_rel        .. "glew_1.7.0/"
local lib_glew_win32_debug =   lib_glew .. "win32/"
local lib_glew_win32_release = lib_glew .. "win32/"
local lib_glew_win64_debug =   lib_glew .. "win64/"
local lib_glew_win64_release = lib_glew .. "win64/"
local lib_glew_linux_32 =      lib_glew .. "linux32/"
local lib_glew_linux_64 =      lib_glew .. "linux64/"
local lib_glew_path = ""

--SFML
local lib_sfml = libs_location_rel      .. "SFML_1.6/"
local lib_sfml_win32_debug =   lib_sfml .. "win32/Debug/"
local lib_sfml_win32_release = lib_sfml .. "win32/Release/"
local lib_sfml_win64_debug =   lib_sfml .. "win64/Debug/"
local lib_sfml_win64_release = lib_sfml .. "win64/Release/"
local lib_sfml_linux_32 =      lib_sfml .. "linux32/"
local lib_sfml_linux_64 =      lib_sfml .. "linux64/"
local lib_sfml_path = ""

--COLLADA DOM
local lib_collada = libs_location_rel      	  .. "collada_dom_2.3.1/"
local lib_collada_win32_debug =   lib_collada .. "win32/Debug/"
local lib_collada_win32_release = lib_collada .. "win32/Release/"
local lib_collada_win64_debug =   lib_collada .. "win64/Debug/"
local lib_collada_win64_release = lib_collada .. "win64/Release/"
local lib_collada_linux_32 =      lib_collada .. "linux32/"
local lib_collada_linux_64 =      lib_collada .. "linux64/"
local lib_collada_path = ""

--Boost
local lib_boost = libs_location_rel       .. "boost_1.48.0/"
local lib_boost_win32_debug =   lib_boost .. "win32/Debug/"
local lib_boost_win32_release = lib_boost .. "win32/Release/"
local lib_boost_win64_debug =   lib_boost .. "win64/Debug/"
local lib_boost_win64_release = lib_boost .. "win64/Release/"
local lib_boost_linux_32 =      lib_boost .. "linux32/"
local lib_boost_linux_64 =      lib_boost .. "linux64/"
local lib_boost_path = ""

--Bullet
local lib_bullet = libs_location_rel        .. "bullet_2.79/"
local lib_bullet_win32_debug =   lib_bullet .. "win32/Debug/"
local lib_bullet_win32_release = lib_bullet .. "win32/Release/"
local lib_bullet_win64_debug =   lib_bullet .. "win64/Debug/"
local lib_bullet_win64_release = lib_bullet .. "win64/Release/"
local lib_bullet_linux_32 =      lib_bullet .. "linux32/"
local lib_bullet_linux_64 =      lib_bullet .. "linux64/"
local lib_bullet_path = ""


--Command line arguments
local action_type = _ACTION
_,count = string.gsub(action_type,"vs","vs")
local is_vs = count > 0 --this tells us if we are using visual studio (it handles "links" differently)
local os_type = _OPTIONS["os"]
local platform_type = _OPTIONS["platform"]
os.rmdir( cwd .. string.gsub(build_location_rel,"/$", "") ) --deletes the old build folder

--This function formats the link files properly
function matchlibs(dir)
	local libs = os.matchfiles(dir .. "*")
	for i=1, #libs do
		libs[i] = string.gsub(libs[i],".lib$", "")
		if is_vs then
			libs[i] = string.gsub(libs[i],dir, "")
		end
	end
	return libs
end

--Set up debug and release versions
solution ( name )
	configurations { "Debug", "Release" }
	defines {"_CRT_SECURE_NO_WARNINGS"}
	defines {"GLEW_STATIC"}
	location ( build_location_rel )
	
project ( name )
	kind ("ConsoleApp")
	language ("C++")
	files { source_location_rel .. "**"}           --include all of our source code (resursive)
	files { data_location_rel .. "**"}           --include all of our data (resursive)
	files { headers_location_rel .. "gl3w/**" }    --include GL3W
	files { headers_location_rel .. "tinyxml/**" } --include tinyxml
	includedirs { headers_location_rel }           --this accounts for all library headers
	includedirs { headers_location_rel .. "bullet/" } --add bullet src directly (because bullet includes its own files incorrectly)
	includedirs { headers_location_rel .. "collada/1.4/" } --add separate collada path
	includedirs { headers_location_rel .. "collada/" } --add separate collada path
	
	location ( build_location_rel )                --this is where the project is built
	debugdir ( root_location_rel )                 --this is where the IDE-generated-exe accesses data and other folders
	targetdir ( build_location_rel )               --this is where the exe gets built
	
	if os_type == "windows" then 
		targetextension ( ".exe" )
	elseif os_type == "linux" then
		targetextension ( ".run" ) 
	end

	--Debug-----------------------------------
	configuration "Debug"
		flags { "Symbols" }
		defines { "DEBUG" }
		                            --DEBUG
		if os_type ==               "windows" then
			if platform_type ==     "x32" then 
				lib_glew_path = 	lib_glew_win32_debug
				lib_sfml_path =     lib_sfml_win32_debug
				lib_collada_path =  lib_collada_win32_debug
				lib_boost_path =    lib_boost_win32_debug
				lib_bullet_path =   lib_bullet_win32_debug
			elseif platform_type == "x64" then 
				lib_glew_path = 	lib_glew_win64_debug
				lib_sfml_path =     lib_sfml_win64_debug
				lib_collada_path =  lib_collada_win64_debug
				lib_boost_path =    lib_boost_win64_debug
				lib_bullet_path =   lib_bullet_win64_debug
			end
			                        --DEBUG
		elseif os_type ==           "linux" then
			if platform_type ==     "x32" then
				lib_glew_path = 	lib_glew_linux_32
				lib_sfml_path =     lib_sfml_linux_32
				lib_collada_path =  lib_collada_linux_32
				lib_boost_path =    lib_boost_linux_32
				lib_bullet_path =   lib_bullet_linux_32
			elseif platform_type == "x64" then
				lib_glew_path = 	lib_glew_linux_64
				lib_sfml_path =     lib_sfml_linux_64
				lib_collada_path =  lib_collada_linux_64
				lib_boost_path =    lib_boost_linux_64
				lib_bullet_path =   lib_bullet_linux_64
			end
		end
		
		--Do this for every build type
		local paths = { lib_glew_path, lib_sfml_path, lib_collada_path, lib_boost_path, lib_bullet_path}
		for i,path in pairs(paths) do
			links(matchlibs(cwd .. path))
			libdirs(path)
		end
	
	--Release-----------------------------------	
	configuration "Release"
		flags { "Optimize" }
		defines { "NDEBUG" }
		                            --RELEASE
		if os_type ==               "windows" then
			if platform_type ==     "x32" then 
				lib_glew_path = 	lib_glew_win32_release
				lib_sfml_path =     lib_sfml_win32_release
				lib_collada_path =  lib_collada_win32_release
				lib_boost_path =    lib_boost_win32_release
				lib_bullet_path =   lib_bullet_win32_release
			elseif platform_type == "x64" then 
				lib_glew_path = 	lib_glew_win64_release
				lib_sfml_path =     lib_sfml_win64_release
				lib_collada_path =  lib_collada_win64_release
				lib_boost_path =    lib_boost_win64_release
				lib_bullet_path =   lib_bullet_win64_release
			end
			                        --RELEASE
		elseif os_type ==           "linux" then
			if platform_type ==     "x32" then
				lib_glew_path = 	lib_glew_linux_32	
				lib_sfml_path =     lib_sfml_linux_32
				lib_collada_path =  lib_collada_linux_32
				lib_boost_path =    lib_boost_linux_32
				lib_bullet_path =   lib_bullet_linux_32  	
			elseif platform_type == "x64" then
				lib_glew_path = 	lib_glew_linux_64
				lib_sfml_path =     lib_sfml_linux_64
				lib_collada_path =  lib_collada_linux_64
				lib_boost_path =    lib_boost_linux_64
				lib_bullet_path =   lib_bullet_linux_64
			end
		end
		
		--Do this for every build type
		local paths = { lib_glew_path, lib_sfml_path, lib_collada_path, lib_boost_path, lib_bullet_path}
		for i,path in pairs(paths) do
			links(matchlibs(cwd .. path))
			libdirs(path)
		end

===================================================================
  Cloud-dev-studio Release process
===================================================================

Download cef_binary_3.2171.1979_linux64 from [1] cefbinary and follow below steps.

1. copy wso2devstudio folder to cefbinary root folder.
2. edit CMakeLists.txt in cefbinary root folder and add following line.
	add_subdirectory(wso2devstudio)
3. Optional
      To avoid compilation of "cefsimple" and "cefclient" sample apps which comes with the binary,
      Remove below two lines from CMakeLists.txt file in cefbinary root folder.
	add_subdirectory(cefsimple)
	add_subdirectory(cefclient)
4. In cefbinary root folder, execute following.

	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug(or Release) 

	IMPORTANT : You should have already installed cmake 2.8.12.2 or later version.

5. To compile wso2devstudio application, simply execute following in the root folder of cefbinary.

	make wso2devstudio



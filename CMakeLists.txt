cmake_minimum_required(VERSION 3.9)
project(masterkeys)

set(LANG en_US.UTF-8)
set(CMAKE_CXX_STANDARD 17)

IF (CYGWIN)
    SET (CMAKE_FIND_LIBRARY_PREFIXES "")
    SET (CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".LIB" ".dll" ".DLL")
ELSE()
#    SET (CMAKE_FIND_LIBRARY_PREFIXES "lib")
#    SET (CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
ENDIF (CYGWIN)

get_filename_component(MASTERKEYS_SDK_DIR "./sdk" REALPATH)
MESSAGE(STATUS "MasterKeys SDK location: " ${MASTERKEYS_SDK_DIR})
find_library(MASTERKEYS_SDK
        NAMES SDKDLL64
        HINTS ${MASTERKEYS_SDK_DIR})
MESSAGE(STATUS "MasterKeys SDK lib: " ${MASTERKEYS_SDK})

include_directories(${MASTERKEYS_SDK_DIR})

add_executable(masterkeys src/main.cpp src/KeyboardLayout.cpp src/KeyboardLayout.h src/KeyData.h src/KeyboardCanvas.cpp src/KeyboardCanvas.h src/utils/ColorUtils.h src/utils/StringUtils.h src/utils/Utils.h src/KeyboardLoader.cpp src/KeyboardLoader.h src/sdk/MasterkeysSdk.cpp src/sdk/MasterkeysSdk.h src/utils/Geometry.h src/effects/KeyboardEffect.h src/KeyboardManager.cpp src/KeyboardManager.h src/effects/RainDropsKeyboardEffect.h src/effects/LockKeysKeyboardEffect.h src/effects/SolidBackgroundKeyboardEffect.h src/effects/CrosshairKeyboardEffect.h src/effects/WaveSimulationKeyboardEffect.h)

target_link_libraries(masterkeys ${MASTERKEYS_SDK})

add_custom_command(TARGET masterkeys POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/sdk/SDKDLL.dll $<TARGET_FILE_DIR:masterkeys>/SDKDLL.dll)

add_custom_command(TARGET masterkeys POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:masterkeys>/data)

add_custom_command(TARGET masterkeys POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/docs $<TARGET_FILE_DIR:masterkeys>/docs)
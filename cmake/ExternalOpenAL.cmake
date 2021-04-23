include(FetchContent)

FetchContent_Declare(
	OpenAL
	GIT_REPOSITORY https://github.com/kcat/openal-soft.git
	GIT_TAG openal-soft-1.21.0
	GIT_SHALLOW TRUE
)
FetchContent_GetProperties(OpenAL)
if(NOT openal_POPULATED)
	FetchContent_Populate(OpenAL)

	set(ALSOFT_UTILS OFF CACHE INTERNAL "")
	set(ALSOFT_NO_CONFIG_UTI =ON CACHE INTERNAL "")
	set(ALSOFT_EXAMPLES OFF CACHE INTERNAL "")
	set(ALSOFT_TESTS OFF CACHE INTERNAL "")
	set(ALSOFT_INSTALL_CONFIG OFF CACHE INTERNAL "")
	set(ALSOFT_INSTALL_HRTF_DATA OFF CACHE INTERNAL "")
	set(ALSOFT_INSTALL_AMBDEC_PRESETS OFF CACHE INTERNAL "")
	set(ALSOFT_BACKEND_WINMM OFF CACHE INTERNAL "")
	set(FORCE_STATIC_VCRT ${FORCE_STATIC_VCRT} CACHE INTERNAL "")
	set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR} CACHE INTERNAL "")
	set(CMAKE_BUILD_TYPE ${CONFIG} CACHE INTERNAL "")
	set(CMAKE_DEBUG_POSTFIX ${MY_DEBUG_POSTFIX} CACHE INTERNAL "")
	if(BUILD_SHARED_LIBS)
		set(LIBTYPE "SHARED" CACHE INTERNAL "")
	else()
		set(LIBTYPE "STATIC" CACHE INTERNAL "")
	endif()

	add_subdirectory(${openal_SOURCE_DIR} ${openal_BINARY_DIR})
endif()

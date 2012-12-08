# - Add flags to compile with extra warnings
#
#  enable_extra_compiler_warnings(<targetname>)
#  globally_enable_extra_compiler_warnings() - to modify CMAKE_CXX_FLAGS, etc
#    to change for all targets declared after the command, instead of per-command
#
#
# Original Author:
# 2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com
# Iowa State University HCI Graduate Program/VRAC
#
# Copyright Iowa State University 2009-2010.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
# Modified by: Scott MacDonald <scott@whitespaceconsideredharmful.com>
#  - Adding more warning options
#  - Can configure level of warnings wanted

if(__enable_extra_compiler_warnings)
	return()
endif()
set(__enable_extra_compiler_warnings YES)

macro(_enable_extra_compiler_warnings_flags)
	set(_flags)
	if(MSVC)
		option(COMPILER_WARNINGS_EXTREME
			"Use compiler warnings that are probably overkill."
			off)
		mark_as_advanced(COMPILER_WARNINGS_EXTREME)
#		set(_flags "/W4")
		set(_flags "/W3 /WX")
		if(COMPILER_WARNINGS_EXTREME)
			set(_flags "${_flags} /Wall /wd4619 /wd4668 /wd4820 /wd4571 /wd4710")
		endif()
	else()
		include(CheckCXXCompilerFlag)
        set(_flags "-Wall -Wextra -Werror ")

        check_cxx_compiler_flag(-Winit-self WARN_INIT_SELF)
        if(WARN_INIT_SELF)
			set(_flags "${_flags} -Winit-self")
		endif()

        check_cxx_compiler_flag(-Wfloat-equal WARN_FLOAT_EQUAL)
        if(WARN_FLOAT_EQUAL)
			set(_flags "${_flags} -Wfloat-equal")
		endif()

        check_cxx_compiler_flag(-Wsign-conversion WARN_SIGN_CONVERSION)
        if(WARN_SIGN_CONVERSION)
			set(_flags "${_flags} -Wsign-conversion")
		endif()

        check_cxx_compiler_flag(-Wuninitialized WARN_UNINITIALIZED)
        if(WARN_UNINITIALIZED)
			set(_flags "${_flags} -Wuninitialized")
		endif()

        check_cxx_compiler_flag(-Wpointer-arith WARN_POINTER_ARITH)
        if(WARN_POINTER_ARITH)
			set(_flags "${_flags} -Wpointer-arith")
		endif()

        check_cxx_compiler_flag(-Wconversion WARN_CONVERSION)
        if(WARN_CONVERSION)
			set(_flags "${_flags} -Wconversion")
		endif()

        check_cxx_compiler_flag(-Wdtor-privacy WARN_DTOR_PRIVACY)
        if(WARN_DTOR_PRIVACY)
			set(_flags "${_flags} -Wdtor-privacy")
		endif()

        check_cxx_compiler_flag(-Wnon-virtual-dtor WARN_NON_VIRTUAL_DTOR)
        if(WARN_NON_VIRTUAL_DTOR)
			set(_flags "${_flags} -Wnon-virtual-dtor")
		endif()

        check_cxx_compiler_flag(-Woverloaded-virtual WARN_OVERLOADED_VIRTUAL)
        if(WARN_OVERLOADED_VIRTUAL)
			set(_flags "${_flags} -Woverloaded-virtual")
		endif()

        check_cxx_compiler_flag(-Wlogical-op WARN_LOGICAL_OP)
        if(WARN_LOGICAL_OP)
			set(_flags "${_flags} -Wlogical-op")
		endif()

        check_cxx_compiler_flag(-Wdouble-promotion WARN_DOUBLE_PROMOTION)
        if(WARN_DOUBLE_PROMOTION)
			set(_flags "${_flags} -Wdouble-promotion")
		endif()

        check_cxx_compiler_flag(-Wnarrowing WARN_NARROWING)
        if(WARN_NARROWING)
			set(_flags "${_flags} -Wnarrowing")
		endif()

        check_cxx_compiler_flag(-Wzero-as-null-pointer-constant WARN_NULL_CONSTANT)
        if(WARN_NULL_CONSTANT)
			set(_flags "${_flags} -Wzero-as-null-pointer-constant")
		endif()

#        check_cxx_compiler_flag(-Wundef WARN_UNDEF)
#        if(WARN_UNDEF)
#			set(_flags "${_flags} -Wundef")
#		endif()

        check_cxx_compiler_flag(-Wcast-qual WARN_CAST_QUAL)
        if(WARN_CAST_QUAL)
            set(_flags "${_flags} -Wcast-qual")
        endif()
	endif()
endmacro()

function(enable_warnings _target)
	_enable_extra_compiler_warnings_flags()
	get_target_property(_origflags ${_target} COMPILE_FLAGS)
	if(_origflags)
		set_property(TARGET
			${_target}
			PROPERTY
			COMPILE_FLAGS
			"${_flags} ${_origflags}")
	else()
		set_property(TARGET
			${_target}
			PROPERTY
			COMPILE_FLAGS
			"${_flags}")
	endif()
endfunction()

function(set_warnings_as_errors _target)
	get_target_property(_origflags ${_target} COMPILE_FLAGS)
	if(_origflags)
		set_property(TARGET
			${_target}
			PROPERTY
			COMPILE_FLAGS
            "-Werror ${_origflags}")
	else()
		set_property(TARGET
			${_target}
			PROPERTY
			COMPILE_FLAGS
            "-Werror")
	endif()
endfunction()
function(globally_enable_extra_compiler_warnings)
	_enable_extra_compiler_warnings_flags()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_flags}" PARENT_SCOPE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_flags}" PARENT_SCOPE)
endfunction()

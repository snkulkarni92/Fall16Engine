/*
	This file provides more advanced assert functionality than the standard library
*/

#ifndef EAE6320_ASSERTS_H
#define EAE6320_ASSERTS_H

// Header Files
//=============

#include "Configuration.h"

#ifdef EAE6320_ASSERTS_AREENABLED
	#include <intrin.h>
	#include <sstream>
#endif

// Helper Function Declaration
//============================

#ifdef EAE6320_ASSERTS_AREENABLED
	namespace eae6320
	{
		namespace Asserts
		{
			// Platform-independent
			bool ShowMessageIfAssertionIsFalseAndReturnWhetherToBreak( const unsigned int i_lineNumber, const char* const i_file,
				bool& io_shouldThisAssertBeIgnoredInTheFuture, const char* const i_message, ... );
			// Platform-specific
			bool ShowMessageAndReturnWhetherToBreak( std::ostringstream& io_message, bool& io_shouldThisAssertBeIgnoredInTheFuture );
		}
	}
#endif

// Interface
//==========

#ifdef EAE6320_ASSERTS_AREENABLED
	#if defined( EAE6320_PLATFORM_WINDOWS )
		#define EAE6320_ASSERTS_BREAK __debugbreak()
	#else
		#error "No implementation exists for breaking on asserts"
	#endif

	#define EAE6320_ASSERT( i_assertion )	\
	{	\
		static bool shouldThisAssertBeIgnored = false;	\
		if ( !shouldThisAssertBeIgnored && !static_cast<bool>( i_assertion )	\
			&& eae6320::Asserts::ShowMessageIfAssertionIsFalseAndReturnWhetherToBreak( __LINE__, __FILE__, shouldThisAssertBeIgnored, "" ) )	\
		{	\
			EAE6320_ASSERTS_BREAK;	\
		}	\
	}
	#define EAE6320_ASSERTF( i_assertion, i_messageToDisplayWhenAssertionIsFalse, ... )	\
	{	\
		static bool shouldThisAssertBeIgnored = false;	\
		if ( !shouldThisAssertBeIgnored && !static_cast<bool>( i_assertion ) \
			&& eae6320::Asserts::ShowMessageIfAssertionIsFalseAndReturnWhetherToBreak( __LINE__, __FILE__,	\
				shouldThisAssertBeIgnored, i_messageToDisplayWhenAssertionIsFalse, __VA_ARGS__ ) )	\
		{	\
			EAE6320_ASSERTS_BREAK;	\
		}	\
	}
#else
	// The macros do nothing when asserts aren't enabled
	#define EAE6320_ASSERT( i_assertion )
	#define EAE6320_ASSERTF( i_assertion, i_messageToDisplayWhenAssertionIsFalse, ... )
#endif

#endif	// EAE6320_ASSERTS_H

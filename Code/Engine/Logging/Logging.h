/*
	This file's functions are used to log messages to a file
	that gets generated every time the game is run
*/

#ifndef EAE6320_LOGGING_H
#define EAE6320_LOGGING_H

// Header Files
//=============

#include "Configuration.h"

#ifndef NULL
	#define NULL 0
#endif

// Interface
//==========

namespace eae6320
{
	namespace Logging
	{
		// Output
		//-------

		bool OutputMessage( const char* const i_message, ... );
		// An error is identical to a message except that the buffer is flushed to disk immediately
		// (this prevents messages from being lost if an application crashes)
		bool OutputError( const char* const i_errorMessage, ... );

		// Initialization / Clean Up
		//--------------------------

		bool Initialize( const char* const i_pathToLogTo = NULL );
		bool CleanUp();
	}
}

#endif	// EAE6320_LOGGING_H

// Header Files
//=============

#include "cbApplication.h"

#include <cstdlib>
#include "../Asserts/Asserts.h"
#include "../Graphics/Graphics.h"
#include "../Logging/Logging.h"
#include "../Time/Time.h"
#include "../UserOutput/UserOutput.h"

// Interface
//==========

// Run
//------

int eae6320::Application::cbApplication::ParseEntryPointParametersAndRun( const sEntryPointParameters& i_entryPointParameters )
{
	int exitCode = EXIT_SUCCESS;

	// Initialize the application
	if ( Initialize_all( i_entryPointParameters ) )
	{
		Logging::OutputMessage( "The application was successfully initialized" );
	}
	else
	{
		exitCode = EXIT_FAILURE;
		EAE6320_ASSERT( false );
		Logging::OutputError( "Application initialization failed!" );
		UserOutput::Print( "Initialization failed! (Check the log file for details.) This program will now exit." );
		goto OnExit;
	}

	// Run the main application logic and wait for it to exit
	if ( !WaitForApplicationToFinish( exitCode ) )
	{
		EAE6320_ASSERT( false );
		UserOutput::Print( "The application encountered an error and will now exit" );
		goto OnExit;
	}

OnExit:

	if ( !CleanUp_all() )
	{
		EAE6320_ASSERT( false );
		// If any clean up fails don't overwrite any non-standard exit code that was explicitly returned by WaitForApplicationToFinish()
		if ( exitCode == EXIT_SUCCESS )
		{
			exitCode = EXIT_FAILURE;
		}
	}

	return exitCode;
}

// Initialization / Clean Up
//--------------------------

bool eae6320::Application::cbApplication::Initialize_all( const sEntryPointParameters& i_entryPointParameters )
{
	// Initialize logging first so that it's always available
	if ( !Logging::Initialize( GetPathToLogTo() ) )
	{
		EAE6320_ASSERT( false );
		return false;
	}
	// Initialize the new application instance with entry point parameters
	if ( !Initialize_base( i_entryPointParameters ) )
	{
		EAE6320_ASSERT( false );
		return false;
	}
	// Initialize engine systems
	if ( !Initialize_engine() )
	{
		EAE6320_ASSERT( false );
		return false;	
	}
	// Initialize the game
	if ( !Initialize() )
	{
		EAE6320_ASSERT( false );
		return false;
	}

	return true;
}

bool eae6320::Application::cbApplication::Initialize_engine()
{
	// User Output
	{
		UserOutput::sInitializationParameters initializationParameters;
		if ( PopulateUserOutputInitializationParameters( initializationParameters ) )
		{
			if ( !UserOutput::Initialize( initializationParameters ) )
			{
				EAE6320_ASSERT( false );
				return false;
			}
		}
		else
		{
			EAE6320_ASSERT( false );
			return false;
		}
	}
	// Time
	if ( !Time::Initialize() )
	{
		EAE6320_ASSERT( false );
		return false;
	}
	// Graphics
	{
		Graphics::sInitializationParameters initializationParameters;
		if ( PopulateGraphicsInitializationParameters( initializationParameters ) )
		{
			if ( !Graphics::Initialize( initializationParameters ) )
			{
				EAE6320_ASSERT( false );
				return false;
			}
		}
		else
		{
			EAE6320_ASSERT( false );
			return false;
		}
	}

	return true;
}

bool eae6320::Application::cbApplication::CleanUp_all()
{
	bool wereThereErrors = false;

	// Clean up the game
	if ( !CleanUp() )
	{
		wereThereErrors = true;
		EAE6320_ASSERT( false );
	}
	// Clean up engine systems
	if ( !CleanUp_engine() )
	{
		wereThereErrors = true;
		EAE6320_ASSERT( false );
	}
	// Clean up the application
	if ( !CleanUp_base() )
	{
		wereThereErrors = true;
		EAE6320_ASSERT( false );
	}
	// Clean up logging last so that messages can still be logged during clean up
	if ( !Logging::CleanUp() )
	{
		wereThereErrors = true;
		EAE6320_ASSERT( false );
	}

	return !wereThereErrors;
}

bool eae6320::Application::cbApplication::CleanUp_engine()
{
	bool wereThereErrors = false;

	// Graphics
	if ( !Graphics::CleanUp() )
	{
		wereThereErrors = true;
		EAE6320_ASSERT( false );
	}
	// Time
	if ( !Time::CleanUp() )
	{
		wereThereErrors = true;
		EAE6320_ASSERT( false );
	}
	// User Output
	if ( !UserOutput::CleanUp() )
	{
		wereThereErrors = true;
		EAE6320_ASSERT( false );
	}

	return !wereThereErrors;
}

eae6320::Application::cbApplication::~cbApplication()
{
	CleanUp_base();
}

// Implementation
//===============

// Run
//----

void eae6320::Application::cbApplication::OnNewFrame()
{
	Time::OnNewFrame();
	Update();
	Graphics::RenderFrame();
}

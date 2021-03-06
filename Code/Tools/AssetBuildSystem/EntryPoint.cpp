/*
	The main() function is where the program starts execution
*/

// Header Files
//=============

#include <cstdlib>
#include "AssetBuild.h"

// Entry Point
//============

int main( int i_argumentCount, char** i_arguments )
{
	bool wereThereErrors = false;

	if ( !eae6320::AssetBuild::Initialize() )
	{
		wereThereErrors = true;
		goto OnExit;
	}

	// The command line should have a list of assets to build
	for ( int i = 1; i < i_argumentCount; ++i )
	{
		const char* const relativePath = i_arguments[i];
		if ( !eae6320::AssetBuild::BuildAsset( relativePath ) )
		{
			wereThereErrors = true;
			// Instead of exiting immediately an attempt should be made to build all assets
			// (both because it gives a better idea of the number of errors
			// but also because it could potentially allow the game to still be run with the
			// assets that _did_ build successfully)
		}
	}

OnExit:

	if ( !eae6320::AssetBuild::CleanUp() )
	{
		wereThereErrors = true;
	}

	if ( !wereThereErrors )
	{
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}

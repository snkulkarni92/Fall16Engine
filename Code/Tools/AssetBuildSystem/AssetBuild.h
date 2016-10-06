/*
	These functions are responsible for building assets
*/

#ifndef EAE6320_ASSETBUILD_H
#define EAE6320_ASSETBUILD_H

// Interface
//==========

namespace eae6320
{
	namespace AssetBuild
	{
		// Build
		//------

		bool BuildAsset( const char* const i_relativePath );

		// Initialization / Clean Up
		//--------------------------

		bool Initialize();
		bool CleanUp();
	}
}

#endif	// EAE6320_ASSETBUILD_H

// Header Files
//=============

#include "cMyGame.h"
#include "../../Engine/Graphics/Graphics.h"

namespace
{
	eae6320::Graphics::Mesh * s_Mesh = NULL;
}
// Interface
//==========

// Initialization / Clean Up
//--------------------------

eae6320::cMyGame::~cMyGame()
{

}

// Inherited Implementation
//=========================

void eae6320::cMyGame::Update()
{
	eae6320::Graphics::SubmitObject(s_Mesh);
}

// Initialization / Clean Up
//--------------------------

bool eae6320::cMyGame::Initialize()
{
	s_Mesh = new eae6320::Graphics::Mesh();
	s_Mesh->Initialize();

	return true;
}

bool eae6320::cMyGame::CleanUp()
{
	s_Mesh->CleanUp();
	return true;
}

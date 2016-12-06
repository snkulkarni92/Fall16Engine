#ifndef EAE6320_MESH_H
#define EAE6320_MESH_H

#if defined( EAE6320_PLATFORM_D3D )
#include <D3D11.h>
#elif defined( EAE6320_PLATFORM_GL )

#include "OpenGL/Includes.h"
#endif

namespace eae6320
{
	namespace Graphics
	{
		class Mesh
		{
		public:
			bool Initialize();
			bool CleanUp();
			bool Draw();
		private:
#if defined( EAE6320_PLATFORM_D3D )
			ID3D11Buffer* m_vertexBuffer = NULL;
#elif defined( EAE6320_PLATFORM_GL )
			GLuint m_vertexArrayId = 0;
			GLuint m_vertexBufferId = 0;
#endif
		};
	}
}

#endif
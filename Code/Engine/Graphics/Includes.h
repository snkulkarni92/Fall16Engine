#ifndef EAE6320_GRAPHICS_INCLUDES_H
#define EAE6320_GRAPHICS_INCLUDES_H
#if defined (EAE6320_PLATFORM_D3D)
#include <D3D11.h>
#elif defined (EAE6320_PLATFORM_GL)

#endif
namespace eae6320
{
	namespace Graphics
	{
		// This struct determines the layout of the geometric data that the CPU will send to the GPU
		struct sVertex
		{
			// POSITION
			// 2 floats == 8 bytes
			// Offset = 0
			float x, y;
		};

		struct GraphicsContext
		{
#if defined (EAE6320_PLATFORM_D3D)
			ID3D11Device* direct3dDevice;
			ID3D11DeviceContext* direct3dImmediateContext;
#elif defined (EAE6320_PLATFORM_GL)

#endif
		};
		void CreateNewGraphicsContext(GraphicsContext context);
		const GraphicsContext & GetContext();
	}
}

#endif

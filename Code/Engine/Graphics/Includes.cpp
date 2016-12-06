#include "Includes.h"

namespace eae6320
{
	namespace Graphics
	{
		GraphicsContext context;

		const GraphicsContext & GetContext()
		{
			return context;
		}
		void CreateNewGraphicsContext(GraphicsContext i_context)
		{
			context.direct3dDevice = i_context.direct3dDevice;
			context.direct3dImmediateContext = i_context.direct3dImmediateContext;
		}
	}
}
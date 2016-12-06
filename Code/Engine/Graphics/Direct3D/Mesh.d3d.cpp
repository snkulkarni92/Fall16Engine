#include "../Mesh.h"
#include "../Includes.h"
#include "../../Logging/Logging.h"
#include "../../Asserts/Asserts.h"

namespace eae6320
{
	namespace Graphics
	{
		bool Mesh::Initialize()
		{
			const unsigned int triangleCount = 2;
			const unsigned int vertexCountPerTriangle = 3;
			const unsigned int vertexCount = triangleCount * vertexCountPerTriangle;
			const unsigned int bufferSize = vertexCount * sizeof(sVertex);
			sVertex vertexData[vertexCount];
			{
				vertexData[0].x = 0.0f;
				vertexData[0].y = 0.0f;

				vertexData[1].x = 1.0f;
				vertexData[1].y = 1.0f;

				vertexData[2].x = 1.0f;
				vertexData[2].y = 0.0f;

				vertexData[3].x = 0.0f;
				vertexData[3].y = 0.0f;

				vertexData[4].x = 0.0f;
				vertexData[4].y = 1.0f;

				vertexData[5].x = 1.0f;
				vertexData[5].y = 1.0f;
			}

			D3D11_BUFFER_DESC bufferDescription = { 0 };
			{
				bufferDescription.ByteWidth = bufferSize;
				bufferDescription.Usage = D3D11_USAGE_IMMUTABLE;	// In our class the buffer will never change after it's been created
				bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				bufferDescription.CPUAccessFlags = 0;	// No CPU access is necessary
				bufferDescription.MiscFlags = 0;
				bufferDescription.StructureByteStride = 0;	// Not used
			}
			D3D11_SUBRESOURCE_DATA initialData = { 0 };
			{
				initialData.pSysMem = vertexData;
				// (The other data members are ignored for non-texture buffers)
			}

			const HRESULT result = GetContext().direct3dDevice->CreateBuffer(&bufferDescription, &initialData, &m_vertexBuffer);
			if (FAILED(result))
			{
				EAE6320_ASSERT(false);
				eae6320::Logging::OutputError("Direct3D failed to create the vertex buffer with HRESULT %#010x", result);
				return false;
			}
			return true;
		}

		bool Mesh::CleanUp()
		{
			if (m_vertexBuffer)
			{
				m_vertexBuffer->Release();
				m_vertexBuffer = NULL;
			}
			return true;
		}

		bool Mesh::Draw()
		{
			// Bind a specific vertex buffer to the device as a data source
			{
				const unsigned int startingSlot = 0;
				const unsigned int vertexBufferCount = 1;
				// The "stride" defines how large a single vertex is in the stream of data
				const unsigned int bufferStride = sizeof(sVertex);
				// It's possible to start streaming data in the middle of a vertex buffer
				const unsigned int bufferOffset = 0;
				GetContext().direct3dImmediateContext->IASetVertexBuffers(startingSlot, vertexBufferCount, &m_vertexBuffer, &bufferStride, &bufferOffset);
			}
			// Render triangles from the currently-bound vertex buffer
			{
				// As of this comment we are only drawing a single triangle
				// (you will have to update this code in future assignments!)
				const unsigned int triangleCount = 2;
				const unsigned int vertexCountPerTriangle = 3;
				const unsigned int vertexCountToRender = triangleCount * vertexCountPerTriangle;
				// It's possible to start rendering primitives in the middle of the stream
				const unsigned int indexOfFirstVertexToRender = 0;
				GetContext().direct3dImmediateContext->Draw(vertexCountToRender, indexOfFirstVertexToRender);
			}
			return true;
		}
	}
}
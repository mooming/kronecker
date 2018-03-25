#include "Renderer.h"

namespace HardBop
{
	Renderer::Renderer()
	{
		Open();
	}

	Renderer::~Renderer()
	{
		Close();
	}

	void Renderer::Render()
	{
	}

	Renderable& Renderer::Create()
	{
		return renderObjs[0];
	}

	void Renderer::Remove(Renderable & renderable)
	{
	}
}

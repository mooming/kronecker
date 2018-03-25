#pragma once

#include <cstdint>

namespace HardBop
{
	class RenderTarget
	{
	private:
		int width;
		int height;
		uint8_t colorDepth;

	public:
		RenderTarget();
	};
}

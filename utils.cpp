#include "stdafx.h"
#include "utils.h"


//네임스페이스는 정의해두면 여러분이 편하게 쓸수있다
namespace THETA_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf((x * x) + (y * y));

		float angle = acosf(x / distance);

		//Y축은 보정이 필요하다
		if (y2 > y1)
		{
			angle = PI * 2 - angle;
			if (angle >= PI * 2) angle -= PI * 2;
		}

		return angle;
	}
}
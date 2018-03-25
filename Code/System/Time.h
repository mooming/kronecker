// Copyright Hansol Park (anav96@naver.com, mooming.go@gmail.com). All rights reserved.

#ifndef Time_h
#define Time_h

#include "Types.h"

namespace HardBop
{
	class Time
	{
	public:
		using MilliSec = uint64_t;

   public:
		class Measure
		{
		private:
			MilliSec& deltaMilli;
			MilliSec start;

		public:
			Measure(MilliSec& deltaMilli) : deltaMilli(deltaMilli)
			{
				start = GetTimeMilli();
			}

			~Measure()
			{
				deltaMilli = GetTimeMilli() - start;
			}
		};

		class MeasureSec
		{
		private:
			float& deltaTime;
			MilliSec start;

		public:
			MeasureSec(float& deltaTime) : deltaTime(deltaTime)
			{
				start = GetTimeMilli();
			}

			~MeasureSec()
			{
				deltaTime = 0.001f * (GetTimeMilli() - start);
			}
		};

   public:
		static MilliSec GetTimeSec();
		static MilliSec GetTimeMilli();
		static void Sleep(MilliSec milli);
	};
}

#endif /* Time_h */

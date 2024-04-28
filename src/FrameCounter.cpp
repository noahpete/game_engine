#include "FrameCounter.h"

int FrameCounter::sFrameNumber;

int FrameCounter::GetFrameNumber()
{
    return sFrameNumber;
}

void FrameCounter::Increment()
{
    sFrameNumber++;
}

void FrameCounter::Reset()
{
    sFrameNumber = 0;
}

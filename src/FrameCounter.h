#pragma once
class FrameCounter
{
public:
	static int GetFrameNumber();
	static void Increment();
	static void Reset();

private:
	static int sFrameNumber;

};


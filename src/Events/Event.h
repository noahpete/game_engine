#pragma once

#include <string>
#include "Util.h"

enum class EventType
{
	None,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPress, KeyRelease,
	MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
};

enum EventCategory
{
	None,
	Application	= BIT(0),
	Input		= BIT(1),
	Keyboard	= BIT(2),
	Mouse		= BIT(3),
	MouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetType() const override { return GetStaticType(); }\
								virtual std::string GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class Event
{
public:
	bool handled_ = false;

	Event() {};
	~Event() {};

	inline bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	};

	virtual EventType GetType() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string GetName() const = 0;
	virtual std::string ToString() const { return GetName(); }

};


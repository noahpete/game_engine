#pragma once

#include <sstream>
#include "Events/Event.h"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height) {}

	unsigned int GetWidth() const { return m_Width; }
	unsigned int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::WindowResize);
	EVENT_CLASS_CATEGORY(EventCategory::Application);

private:
	unsigned int m_Width, m_Height;

};


class WindowCloseEvent : public Event
{
public:
	EVENT_CLASS_TYPE(EventType::WindowClose);
	EVENT_CLASS_CATEGORY(EventCategory::Application);

};

class AppTickEvent : public Event
{
public:
	EVENT_CLASS_TYPE(EventType::AppTick);
	EVENT_CLASS_CATEGORY(EventCategory::Application);

};


class AppUpdateEvent : public Event
{
public:
	EVENT_CLASS_TYPE(EventType::AppUpdate);
	EVENT_CLASS_CATEGORY(EventCategory::Application);

};


class AppRenderEvent : public Event
{
public:
	EVENT_CLASS_TYPE(EventType::AppRender);
	EVENT_CLASS_CATEGORY(EventCategory::Application);

};
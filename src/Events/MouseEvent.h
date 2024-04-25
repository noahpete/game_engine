#pragma once

#include <sstream>
#include "SDL2/SDL.h"
#include "Events/Event.h"

class MouseMoveEvent : public Event
{
public:
	MouseMoveEvent(const float x, const float y)
		: m_X(x), m_Y(y) {}

	float GetX() const { return m_X; }
	float GetY() const { return m_Y; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMoveEvent: " << m_X << ", " << m_Y;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::MouseMove);
	EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input);

private:
	float m_X, m_Y;
};


class MouseScrollEvent : public Event
{
public:
	MouseScrollEvent(const float xOffset, const float yOffset)
		: m_XOffset(xOffset), m_YOffset(yOffset) {}

	float GetXOffset() const { return m_XOffset; }
	float GetYOffset() const { return m_YOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrollEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::MouseScroll);
	EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input);

private:
	float m_XOffset, m_YOffset;
};


class MouseButtonEvent : public Event
{
public:
	SDL_Scancode GetMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input | EventCategory::MouseButton);

protected:
	SDL_Scancode m_Button;

	MouseButtonEvent(const SDL_Scancode button)
		: m_Button(button) {}
};


class MouseButtonPressEvent : public MouseButtonEvent
{
public:
	MouseButtonPressEvent(const SDL_Scancode button)
		: MouseButtonEvent(button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::MouseButtonPress);

};


class MouseButtonReleaseEvent : public MouseButtonEvent
{
public:
	MouseButtonReleaseEvent(const SDL_Scancode button)
		: MouseButtonEvent(button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleaseEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::MouseButtonRelease);

};
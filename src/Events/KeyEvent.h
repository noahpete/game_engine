#pragma once

#include <sstream>
#include "Events/Event.h"
#include "SDL2/SDL.h"


class KeyEvent : public Event
{
public:
	SDL_Scancode GetKeyCode() const { return m_KeyCode; }

	EVENT_CLASS_CATEGORY(EventCategory::Keyboard | EventCategory::Input);

protected:
	SDL_Scancode m_KeyCode;

	KeyEvent(const SDL_Scancode keycode)
		: m_KeyCode(keycode) {}
};


class KeyPressEvent : KeyEvent
{
public:
	KeyPressEvent(const SDL_Scancode keycode, bool isRepeat = false)
		: KeyEvent(keycode), m_IsRepeat(isRepeat) {}

	bool IsRepeat() const { return m_IsRepeat; }
	
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::KeyPress);

private:
	bool m_IsRepeat;
};


class KeyReleaseEvent : KeyEvent
{
public:
	KeyReleaseEvent(const SDL_Scancode keycode)
		: KeyEvent(keycode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::KeyRelease);
};
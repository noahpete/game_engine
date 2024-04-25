#include "InputHandler.h"

InputHandler::InputHandler()
{
	ResetKeys();
}

void InputHandler::ProcessEvent(const SDL_Event* e)
{
	SDL_Scancode keycode = e->key.keysym.scancode;
	InputState& keyState = m_KeyStates[keycode];

	if (e->type == SDL_KEYDOWN)
	{
		switch (keyState)
		{
		case UP:
		case JUST_BECAME_UP:
			GE_CORE_INFO(std::to_string(static_cast<int>(keycode)) + " key was pressed");
			keyState = JUST_BECAME_DOWN;
			break;
		case DOWN:
		case JUST_BECAME_DOWN:
			GE_CORE_INFO(std::to_string(static_cast<int>(keycode)) + " key is pressed");
			keyState = DOWN;
			break;
		}
	}

	if (e->type == SDL_KEYUP)
	{
		switch (keyState)
		{
		case UP:
		case JUST_BECAME_UP:
		case DOWN:
		case JUST_BECAME_DOWN:
			GE_CORE_INFO(std::to_string(static_cast<int>(keycode)) + " key was released");
			keyState = JUST_BECAME_UP;
			break;
		}
	}

	if (e->type == SDL_MOUSEMOTION)
	{
		//GE_CORE_INFO("Mouse move (" + std::to_string(e->motion.x) + ", " + std::to_string(e->motion.y) + ")");
		m_MousePosition = { static_cast<float>(e->motion.x), static_cast<float>(e->motion.y) };
	}

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		GE_CORE_INFO(std::to_string(e->button.button) + " mouse button was pressed");
		m_MouseButtonStates[e->button.button] = JUST_BECAME_DOWN;
	}

	if (e->type == SDL_MOUSEBUTTONUP)
	{
		GE_CORE_INFO(std::to_string(e->button.button) + " mouse button was released");
		m_MouseButtonStates[e->button.button] = JUST_BECAME_UP;
	}

	if (e->type == SDL_MOUSEWHEEL)
	{
		GE_CORE_INFO("Mouse wheel scrolled " + std::to_string(e->wheel.preciseY));
		m_MouseScrollDelta = e->wheel.preciseY;
	}
}

void InputHandler::Update()
{
	for (int code = SDL_SCANCODE_UNKNOWN; code < SDL_NUM_SCANCODES; ++code)
	{
		InputState& keyState = m_KeyStates[static_cast<SDL_Scancode>(code)];

		if (keyState == JUST_BECAME_DOWN)
			keyState = DOWN;

		if (keyState == JUST_BECAME_UP)
			keyState = UP;
	}

	for (auto& button_state : m_MouseButtonStates)
	{
		if (button_state.second == JUST_BECAME_DOWN)
			button_state.second = DOWN;

		if (button_state.second == JUST_BECAME_UP)
			button_state.second = UP;
	}
}

void InputHandler::LateUpdate()
{
	m_MouseScrollDelta = 0.0f;
}

void InputHandler::ResetKeys()
{
	for (int code = SDL_SCANCODE_UNKNOWN; code < SDL_NUM_SCANCODES; ++code)
	{
		m_KeyStates[static_cast<SDL_Scancode>(code)] = JUST_BECAME_UP;
	}
}

bool InputHandler::GetKey(std::string key)
{
	if (Scancodes.find(key) == Scancodes.end()) return false;
	SDL_Scancode keycode = Scancodes.find(key)->second;
	InputState keyState = m_KeyStates[keycode];
	return keyState == DOWN || keyState == JUST_BECAME_DOWN;
}

bool InputHandler::GetKeyDown(std::string key)
{
    return false;
}

bool InputHandler::GetKeyUp(std::string key)
{
    return false;
}

glm::vec2 InputHandler::GetMousePosition()
{
    return glm::vec2();
}

bool InputHandler::GetMouseButton(int button)
{
    return false;
}

bool InputHandler::GetMouseButtonDown(int button)
{
    return false;
}

bool InputHandler::GetMouseButtonUp(int button)
{
    return false;
}

float InputHandler::GetMouseScrollDelta()
{
    return 0.0f;
}

#include "KeyEvent.h"

#include "../Enums/KeyBoard.h"

namespace Core
{
	KeyEvent::KeyEvent() 
		: type(Event::EventType::NONE), 
		  isPressed(false), 
		  key(KeyBoard::Key::NONE)
	{	}

	KeyEvent::KeyEvent(Event::EventType type, bool isPressed, KeyBoard::Key key)
		: type(type),
		  isPressed(isPressed), 
		  key(key)
	{	}

	Event::EventType KeyEvent::GetType() const { return type; }
	bool KeyEvent::GetIsPressed() const { return isPressed; }
	void KeyEvent::SetKey(KeyBoard::Key key) { this->key = key; }
	KeyBoard::Key KeyEvent::GetKey() const { return key; }

	KeyEvent::~KeyEvent()
	{	}
}
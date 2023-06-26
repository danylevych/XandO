#pragma once

#include "IEvent.h"
#include "../Event/Event.h"
#include "../Enums/KeyBoard.h"

namespace Core
{
	class KeyEvent : public IEvent
	{
	protected:
		Event::EventType type;
		bool isPressed;
		KeyBoard::Key key;

	protected:
		KeyEvent();
		KeyEvent(Event::EventType type, bool isPressed, KeyBoard::Key key);

	public:
		KeyEvent(KeyEvent&& other) = delete;
		KeyEvent(const KeyEvent& other) = delete;
		KeyEvent& operator=(KeyEvent&& other) = delete;
		KeyEvent& operator=(const KeyEvent& other) = delete;

	public:
		Event::EventType GetType() const;
		bool GetIsPressed() const;
		void SetKey(KeyBoard::Key key);
		KeyBoard::Key GetKey() const;

	public:
		virtual ~KeyEvent() override;
	};


	class KeyPressed : public KeyEvent
	{
	public:
		KeyPressed(KeyBoard::Key key = KeyBoard::Key::NONE)
			: KeyEvent(Event::EventType::KEY_PRESSED, true, key)
		{	}

	public:
		virtual ~KeyPressed() override = default;
	};

	class KeyReleased : public KeyEvent
	{
	public:
		KeyReleased(KeyBoard::Key key = KeyBoard::Key::NONE)
			: KeyEvent(Event::EventType::KEY_PRESSED, false, key)
		{	}

	public:
		virtual ~KeyReleased() override = default;
	};
}
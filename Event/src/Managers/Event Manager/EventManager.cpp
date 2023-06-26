#include "EventManager.h"

#include <conio.h>
#include <Windows.h>

namespace Core
{
	KeyEvent* EventManager::event = nullptr;
	bool EventManager::firstCalling = true;

	bool EventManager::PollKeyEvent(Event& e)
	{
		if (_kbhit())
		{
			int8_t key = _getch();
			if (key == static_cast<int8_t>(KeyBoard::Key::IS_ARROW))
			{
				switch (static_cast<KeyBoard::Key>(_getch()))
				{
				case KeyBoard::Key::UP:
					event = new KeyPressed(KeyBoard::Key::UP);
					e.Bind(event->GetType(), event);
					break;

				case KeyBoard::Key::DOWN:
					event = new KeyPressed(KeyBoard::Key::DOWN);
					e.Bind(event->GetType(), event);
					break;

				case KeyBoard::Key::LEFT:
					event = new KeyPressed(KeyBoard::Key::LEFT);
					e.Bind(event->GetType(), event);
					break;

				case KeyBoard::Key::RIGHT:
					event = new KeyPressed(KeyBoard::Key::RIGHT);
					e.Bind(event->GetType(), event);
					break;
				}
			}
			else
			{
				short vk = VkKeyScanW(key);

				
				if ((GetAsyncKeyState(vk) & 0x0001) != 0)
				{
					if (vk == static_cast<short>(KeyBoard::Key::ENTER))
					{
						event = new KeyPressed(KeyBoard::Key::ENTER);
						e.Bind(event->GetType(), event);
					}
					else if (vk == static_cast<short>(KeyBoard::Key::ESC))
					{
						event = new KeyPressed(KeyBoard::Key::ESC);
						e.Bind(event->GetType(), event);
					}
					else if (vk >= static_cast<short>(KeyBoard::Key::A) && vk <= static_cast<short>(KeyBoard::Key::Z))
					{
						event = new KeyPressed(static_cast<KeyBoard::Key>(vk));
						e.Bind(event->GetType(), event);
					}					
				}
			}
			return true;
		}
		else
		{
			auto tempKeyEvent = dynamic_cast<KeyEvent*>(e.GetEvent());

			if (tempKeyEvent == nullptr || firstCalling)
			{
				e.Bind(Event::EventType::NONE, nullptr);
				firstCalling = false;
			}
			else
			{
				event = new KeyReleased(tempKeyEvent->GetKey());
				e.Bind(Event::EventType::KEY_RELEASED, event);
				firstCalling = true;
			}

			return false;
		}
	}

	KeyEvent* EventManager::ParseKeyEvent(Event& e)
	{
		return dynamic_cast<KeyEvent*>(e.GetEvent());
	}
}
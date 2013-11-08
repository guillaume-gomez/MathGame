#include <iostream>

#include <SFML/Graphics.hpp>

#include "TextAreaSFML2_0.hpp"

using namespace sf;

int main()
{
	RenderWindow App(VideoMode(800,600), "TextAreaSFML2_0");

	TextAreaSFML2_0 functionInput(0);
	functionInput.setPosition(200,50);
	functionInput.setCharacterSize(20);

	while(App.isOpen())
	{
		Event event;

		while(App.pollEvent(event))
		{
			switch(event.type)
			{
			case Event::Closed:
				App.close();
				break;

			case Event::TextEntered:
				functionInput.insertCharacter(event.text.unicode);
				break;

			case Event::KeyPressed:
				switch(event.key.code)
				{
				case Keyboard::BackSpace:
					functionInput.erase();
					break;

				case Keyboard::Delete:
					functionInput.eraseNext();
					break;

				case Keyboard::Left:
					functionInput.moveCaretBackward();
					break;

				case Keyboard::Right:
					functionInput.moveCaretForward();
					break;

				default:
					break;
				}
			default:
				break;
			}
		}
		App.clear(Color(159,187,177));
		functionInput.blinkCaret(500);
		App.draw(functionInput);
		App.display();
	}

    return 0;
}

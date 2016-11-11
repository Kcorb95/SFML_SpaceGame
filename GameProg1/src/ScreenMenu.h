#include "Screen.h"

using namespace sf;

class ScreenMenu : public Screen
{
private:
	bool playing;
public:
	ScreenMenu(void);
	virtual int Run(sf::RenderWindow &window);
};
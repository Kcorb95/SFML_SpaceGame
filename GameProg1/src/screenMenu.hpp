#include "Screen.hpp"

using namespace sf;

class ScreenMenu : public Screen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
public:
	ScreenMenu(void);
	virtual int Run(sf::RenderWindow &window);
};
#include "cScreen.hpp"

using namespace sf;

class screenMenu : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
public:
	screenMenu(void);
	virtual int Run(sf::RenderWindow &window);
};
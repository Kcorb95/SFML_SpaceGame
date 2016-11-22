#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
	unsigned int m_StartFrame;
	unsigned int m_EndFrame;

	float m_Duration;

	Animation(unsigned int startFrame, unsigned int endFrame, float duration)
	{
		this->m_StartFrame = startFrame;
		this->m_EndFrame = endFrame;
		this->m_Duration = duration;
	}

	unsigned int getLength()
	{
		return m_EndFrame - m_StartFrame + 1;
	}
};

class AnimationHandler
{
private:
	//Vector of animations
	std::vector<Animation> m_Animations;

	//Current time since the animation loop began
	float t;

	int m_CurrentAnim;

public:
	//Add a new animation
	void addAnim(Animation& animation);

	//Update the current frame of animation. dt is the time since the update was last called (ie the time for one frame to be executed)
	void update(const float dt);

	//Change the animation, resetting t in the process
	void changeAnim(unsigned int animNum);

	//Current section of the texture that should be displayed
	sf::IntRect m_Bounds;

	//Pixel dimensions of each individual frame
	sf::IntRect m_FrameSize;

	//Constructor
	AnimationHandler()
	{
		this->t = 0.0f;
		this->m_CurrentAnim = -1;
	}
	AnimationHandler(const sf::IntRect& framesize)
	{
		this->m_FrameSize = framesize;

		this->t = 0.0f;
		this->m_CurrentAnim = -1;
	}
};
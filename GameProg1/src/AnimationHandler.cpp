#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"

void AnimationHandler::update(const float dt)
{
	if (m_CurrentAnim >= this->m_Animations.size() || m_CurrentAnim < 0)
		return;
	float duration = this->m_Animations[m_CurrentAnim].m_Duration;

	//Check if the animation has progressed to a new frame and if so change to the next frame
	if (int((t + dt) / duration) > int(t / duration))
	{
		//Calculate the frame num
		int frame = int((t + dt) / duration);

		//Adjust for looping
		frame %= this->m_Animations[m_CurrentAnim].getLength();

		//Set the sprite to the new frame
		sf::IntRect rect = this->m_FrameSize;
		rect.left = rect.width * frame;
		rect.top = rect.height * this->m_CurrentAnim;
		this->m_Bounds = rect;
	}

	//Increment the time elapsed
	this->t += dt;
	//Adjust for lopping
	if (this->t > duration * this->m_Animations[m_CurrentAnim].getLength())
	{
		this->t = 0.0f;
	}
	return;
}

void AnimationHandler::addAnim(Animation& animation)
{
	this->m_Animations.push_back(animation);
	return;
}

void AnimationHandler::changeAnim(unsigned int animationID)
{
	//Do not change the animation if the animation is currently active or the new animation does not exist
	if (this->m_CurrentAnim == animationID || animationID >= this->m_Animations.size() || animationID < 0)
		return;

	//Set the current animation
	this->m_CurrentAnim = animationID;
	//Update the current animation bounds
	sf::IntRect rect = this->m_FrameSize;
	rect.top = rect.height * animationID;
	this->m_Bounds = rect;
	this->t = 0.0;
	return;
}
#pragma once

struct ISoundPlayer
{
	virtual void setSoundBuffer(const sf::SoundBuffer& soundbuffer) = 0;
};
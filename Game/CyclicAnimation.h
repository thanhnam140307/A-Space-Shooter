#pragma once
#include "Animation.h"
class CyclicAnimation :
  public Animation
{
public:

  virtual void update(float deltaT) override;
  virtual unsigned int getNextFrame() const override;
  float getPercentage() const override;
protected:
  CyclicAnimation(sf::Sprite& s, float length);

private:
  float timeOrientation;
};


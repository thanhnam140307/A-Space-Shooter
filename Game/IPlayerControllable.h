#pragma once

struct Inputs;
struct IPlayerControllable
{
  virtual void update(const Inputs& inputs) = 0;
};

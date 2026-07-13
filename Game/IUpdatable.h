#pragma once

struct IUpdatable
{
  virtual void update(float elaspedTime = 0) = 0;
};

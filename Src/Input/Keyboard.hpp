#pragma once

#include <bitset>

#include "Input/Types.hpp"
#include "Utils/Types.hpp"

class Keyboard
{
  public:
    void update();
    void setKey(s32 key);
    bool checkKeyAndState(s32 key, IState state) const;

  private:
    std::bitset<512> currState = 0;
    std::bitset<512> prevState = 0;
};

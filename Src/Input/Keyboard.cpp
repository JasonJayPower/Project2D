#include "Keyboard.hpp"

void Keyboard::update()
{
    prevState = currState;
}

void Keyboard::setKey(s32 key)
{
    // (REVISIT) We can flip the bits as we dont support repeatable keys yet, or will we ?.
    if (key != -1) {
        currState[key].flip();
    }
}

bool Keyboard::checkKeyAndState(s32 key, IState state) const
{
    if (prevState[key]) {
        return !currState[key] ? IState::Release == state : IState::Hold == state;
    }
    return (currState[key] && (IState::Press == state || IState::Hold == state));
}

#include <Arduino.h>
#include "Button.h"

#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

class ButtonsHandler {

public:
    ButtonsHandler(Button button1, Button button2);

    void setCallbacks(
            std::function<void()> _onPressedButton1,
            std::function<void()> _onPressedButton2,
            std::function<void()> _onPressedBoth
    );
    void setCallbacks(
            std::function<void()> _onPressedButton1,
            std::function<void()> _onPressedButton2,
            std::function<void()> _onPressedBoth,
            std::function<void()> _onPressedBothLong
    );
    void setDebounceTime(unsigned int time);
    void setLongPressTime(unsigned int time);
    void poll();

private:
    Button button1;
    Button button2;

    unsigned int debounceTime = 20;
    unsigned int longPressTime = 1000;

    bool isPressedBothLongSupported = false;
    bool bothClicked = false;
    unsigned long lastStartPressed = 0;

    std::function<void()> onPressedButton1;
    std::function<void()> onPressedButton2;
    std::function<void()> onPressedBoth;
    std::function<void()> onPressedBothLong;

    bool pollState(Button &button) const;
    void resetState(Button &button) const;
    bool isPressed(Button &button) const;
    bool wasPressed(Button &button) const;
    bool isReleased(Button &button) const;
    bool wasReleased(Button &button) const;
    bool isLongPressed() const;
};

#endif //BUTTON_HANDLER_H
#include "ButtonsHandler.h"

ButtonsHandler::ButtonsHandler(Button button1, Button button2) : button1(button1), button2(button2) {}

void ButtonsHandler::setCallbacks(
        std::function<void()> _onPressedButton1,
        std::function<void()> _onPressedButton2,
        std::function<void()> _onPressedBoth) {

    onPressedButton1 = std::move(_onPressedButton1);
    onPressedButton2 = std::move(_onPressedButton2);
    onPressedBoth = std::move(_onPressedBoth);
}

void ButtonsHandler::setCallbacks(
        std::function<void()> _onPressedButton1,
        std::function<void()> _onPressedButton2,
        std::function<void()> _onPressedBoth,
        std::function<void()> _onPressedBothLong) {

    onPressedButton1 = std::move(_onPressedButton1);
    onPressedButton2 = std::move(_onPressedButton2);
    onPressedBoth = std::move(_onPressedBoth);
    onPressedBothLong = std::move(_onPressedBothLong);
    isPressedBothLongSupported = true;
}

void ButtonsHandler::setDebounceTime(unsigned int time) {
    debounceTime = time;
}

void ButtonsHandler::setLongPressTime(unsigned int time) {
    longPressTime = time;
}

bool ButtonsHandler::pollState(Button &button) const {
    auto &s = button.state;
    bool stateChanged = false;
    bool currentRawState = button.invertedState == !digitalRead(button.pin);
    if (s.lastRawState != currentRawState) {
        bool moreThanDebounceTime = (unsigned long) (millis() - s.lastChangeTime) >= debounceTime;
        if (moreThanDebounceTime) {
            s.currentState = currentRawState;
            s.lastChangeTime = millis();
            stateChanged = true;
        }
    }
    s.lastRawState = currentRawState;
    return stateChanged;
}

void ButtonsHandler::resetState(Button &button) const {
    button.state.lastState = button.state.currentState;
}

bool ButtonsHandler::isReleased(Button &button) const {
    return button.state.lastState == RELEASED && button.state.currentState == RELEASED;
}

bool ButtonsHandler::isPressed(Button &button) const {
    return button.state.lastState == PRESSED && button.state.currentState == PRESSED;
}

bool ButtonsHandler::wasPressed(Button &button) const {
    return button.state.lastState == PRESSED && button.state.currentState == RELEASED;
}

bool ButtonsHandler::wasReleased(Button &button) const {
    return button.state.lastState == RELEASED && button.state.currentState == PRESSED;
}

bool ButtonsHandler::isLongPressed() const {
    return millis() - lastStartPressed >= longPressTime && lastStartPressed != 0;
}

void ButtonsHandler::poll() {
    pollState(button1);
    pollState(button2);

    if (wasPressed(button1) && !bothClicked) {
        if (isPressed(button2)) {
            bothClicked = true;
        } else {
            onPressedButton1();
        }
    } else if (wasPressed(button2) && !bothClicked) {
        if (isPressed(button1)) {
            bothClicked = true;
        } else {
            onPressedButton2();
        }
    } else if (isPressedBothLongSupported && wasReleased(button1) || wasReleased(button2)) {
        lastStartPressed = millis();
    } else if (bothClicked && isReleased(button1) && isReleased(button2)) {
        bothClicked = false;
        if (isPressedBothLongSupported && isLongPressed()) {
            lastStartPressed = 0;
            onPressedBothLong();
        } else {
            onPressedBoth();
        }
    }

    resetState(button1);
    resetState(button2);
}

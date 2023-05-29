# Two Buttons Interface


Library handles events when pressing buttons. It supports single clicks and simultaneous clicks of two buttons. It contain debouncer. It is useful to create simple projects with graphical interface when buttons are used to navigate through menu. I was not able to find similar library (that handles simulatanous clicks) so I created this.

Set up is very simple just create two button objects - they needs pin number and mode IN_PULLUP or IN_PULLDOWN - this based on your wiring, if you connects button to 3.3V - then IN_PULLDOWN, when to ground then IN_PULLUP.

pass it to ButtonHandler and create callbacks for actions pressed1, pressed2, pressedBoth.
Inside loop buttonhandler will be listening for button events. Additionally user can specify different than default debounce time.

Same example in dir examples.

#### PLEASE NOTE: actual callbacks are executed when button is released - this is necessary to be able to handle simultanous click.

```
#define NEXT_BUTTON 12
#define PREVIOUS_BUTTON 13

Button button1(PREVIOUS_BUTTON, IN_PULLDOWN);
Button button2(NEXT_BUTTON, IN_PULLDOWN);

ButtonsHandler buttonsHandler(button1, button2);

void pressed1() { Serial.println("Button1 pressed"); }

void pressed2() { Serial.println("Button2 pressed"); }

void pressedBoth() { Serial.println("Both pressed"); }


void setup() {
    Serial.begin(115200);
    buttonsHandler.setCallbacks(pressed1,pressed2,pressedBoth);
}


void loop() {
    buttonsHandler.poll();
}
```

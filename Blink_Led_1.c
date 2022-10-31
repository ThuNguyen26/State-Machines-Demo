#include <stdint.h>
#include <stdbool.h>

#define Blink_Time 500
#define Led_Pin 15

typedef enum
{
  Reset = 0,
  Check_Times,
  Check_Led_State,
  Turn_On_Led,
  Turn_Off_Led
} STATE;

uint64_t t0, t1;
bool Led_State;
STATE state;

void setup()
{
  pinMode(Led_Pin, OUTPUT);
  state = Reset;
  digitalWrite(Led_Pin, HIGH);
}

void loop()
{
  switch (state)
  {
  case Reset:
    t0 = millis();
    state = Check_Times;
    break;
  case Check_Times:
    t1 = millis();
    if ((t1 - t0) > Blink_Time)
      state = Check_Led_State;
    break;
  case Check_Led_State:
    Led_State = digitalRead(Led_Pin);
    if (Led_State == HIGH)
      state = Turn_Off_Led;
    else
      state = Turn_On_Led;
    break;
  case Turn_On_Led:
    digitalWrite(Led_Pin, HIGH);
    state = Reset;
    break;
  case Turn_Off_Led:
    digitalWrite(Led_Pin, LOW);
    state = Reset;
    break;
  }
}

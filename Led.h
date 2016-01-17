

/// Allows control and dimming of a single LED channel.

#pragma once

#include "Constants.h"

class Led
{
public:
  Led(int pin) :
    m_pin(pin),
    m_delay(0),
    m_time(0),
    m_value(0),
    m_value_actual(0)
  {
  }

  void setup()
  {
    pinMode(m_pin, OUTPUT);
  }

  void set(long value)
  {
    int key = map(value,0,255,0,PWM_VALUE);
    key = constrain(key,0,PWM_VALUE);
    m_value = gamma_table[key];

    int diff = abs(m_value - m_value_actual);

    if(diff > 0) {
      // set how long each step will take, if we want it to take TRANSITION_TIME
      // to completely transfer.
      m_delay = TRANSITION_TIME / diff;
    }
  }

  void update()
  {
    if(millis() - m_time >= m_delay)
    {
      m_time = millis();
      if(m_value != m_value_actual)
      {
        if(m_value_actual > m_value)
        {
          m_value_actual = m_value_actual - 1;
        }
        else
        {
          m_value_actual++;
        }
      }
      analogWrite(m_pin, m_value_actual);
    }
  }

private:
  const int m_pin;
  int m_delay;
  unsigned long m_time;
  int m_value;
  int m_value_actual;
};

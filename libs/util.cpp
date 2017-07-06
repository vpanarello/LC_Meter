
#include "util.h"
#include "Arduino.h"

char *float2s(float* f, unsigned int digits)
{
  int index = 0;
  static char s[16]; // buffer to build string representation
  // handle sign
  if (*f < 0.0)
  {
    s[index++] = '-';
    *f = -*f;
  }
  // handle infinite values
  if (isinf(*f))
  {
    strcpy(&s[index], "INF");
    return s;
  }
  // handle Not a Number
  if (isnan(*f))
  {
    strcpy(&s[index], "NaN");
    return s;
  }

  // max digits
  if (digits > 6)
    digits = 6;
  long multiplier = pow(10, digits); // fix int => long

  int exponent = int(log10(*f));
  float g = *f / pow(10, exponent);
  if ((g < 1.0) && (g != 0.0))
  {
    g *= 10;
    exponent--;
  }

  long whole = long(g);                       // single digit
  long part = long((g - whole) * multiplier); // # digits
  char format[16];
  sprintf(format, "%%ld.%%0%dld E%%+d", digits);
  sprintf(&s[index], format, whole, part, exponent);

  return s;
}

#define Ra 14.88E3  /* 14,88 Kohm */
#define Rb 33.26E3  /* 33,26 Kohm */

/*
C  =         1          * C_FACTOR 
    -------------------
    LN(2)*(Ra + 2*Rb).f

C  =  FIX_FACTOR  
    -------------
          f

FIX_FACTOR = 1 / ( LN(2) * (Ra + 2*Rb) )
*/

#define FIX_FACTOR 1.77235263008E-5


char* freq2Cap(uint32_t* f)
{
  float zero_offset = 3.697E-11;
  float capacitance = FIX_FACTOR /  (*f) - zero_offset;
  return float2s(&capacitance, 3);;
}
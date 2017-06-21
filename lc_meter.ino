
#include "frequency_counter.h"
#include "timer_one.h"
#include <LiquidCrystal.h>
#include "util.h"

/* PORT B */
#define LCD_DB7 15 /* pin 15 */
#define LCD_DB6 14 /* pin 14 */
#define LCD_DB4 16 /* pin 16 */
#define LCD_DB3 10 /* pin 10 */

/* PORT F */
#define LCD_EN 18 /* pin A0 */
#define LCD_RS 19 /* pin A1 */
/* PORT D */
#define LCD_LED 4
#define LCD_LIGHT_ON ports->state_d &= ~(1 << LCD_LED)
#define LCD_LIGHT_OFF ports->state_d |= (1 << LCD_LED)

FrequencyCounter *fcounter;
TimerOne *timerone;
/* LiquidCrystal lcd(RS, EN, D4, D5, D6, D7) */
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB3, LCD_DB4, LCD_DB6, LCD_DB7);

void second_tick()
{
  timer0->control_b = NO_CLOCK_SOURCE;
  lcd.clear();
  lcd.print(*fcounter->get_counter_pointer());
  lcd.print(" Hz");
  
  lcd.setCursor(1, 2);
  lcd.print(freq2Cap(fcounter->get_counter_pointer()));
  lcd.print(" F");
  fcounter->clear_counter();
  timer0->control_b = EXTERNAL_CLOCK_SOURCE;
}

#define OS_OFFSET 1148
#define ONE_SECOND_TIME 15625 + OS_OFFSET

void setup()
{
  ports->direction_d |= (1 << LCD_LED);
  LCD_LIGHT_OFF;

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("VPF Tecnologia");
  lcd.setCursor(1, 2);
  lcd.print("ver.1.0/2017");
  LCD_LIGHT_ON;
  _delay_ms(2000);

  fcounter = new FrequencyCounter();
  timerone = new TimerOne(CLK_DIV_1024, WAVEFORM_CTC_OCR1A);
  timer1->compare_a = ONE_SECOND_TIME;
  timerone->set_cb_comparator_a(&second_tick);
}

void loop()
{
  _delay_us(1000);
}

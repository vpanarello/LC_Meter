
#include "frequency_counter.h"
#include "timer_one.h"
#include <LiquidCrystal.h>
#include "util.h"
#include "keyboard.h"

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

#define INDICATOR_LED_YELLOW 0 /* PORTB */
#define INDICATOR_LED_GREEN 5 /* PORTD */

FrequencyCounter *fcounter;
TimerOne *timerone;
/* LiquidCrystal lcd(RS, EN, D4, D5, D6, D7) */
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB3, LCD_DB4, LCD_DB6, LCD_DB7);

Keyboard *keys;

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

void presskey_00() {
  Serial.println("Key 0");
}
void presskey_01() {
  Serial.println("Key 1");
}
void presskey_02() {
  Serial.println("Key 2");
}
void presskey_03() {
  Serial.println("Key 3");
}
void presskey_04() {
  Serial.println("Key 4");
}
void presskey_05() {
  Serial.println("Key 5");
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
  keys = new Keyboard();
  keys->set_callback(&presskey_00);
  keys->set_callback(&presskey_01);
  keys->set_callback(&presskey_02);
  keys->set_callback(&presskey_03);
  keys->set_callback(&presskey_04);
  // keys->set_callback(&presskey_05);

  ports->direction_b |= (1 << INDICATOR_LED_YELLOW);
}

boolean pin_change;

void loop()
{
  
  for(uint8_t i = 0; i < 200; i++) {
    _delay_ms(5);
    keys->check_keys();
  }
  
  
  // dump_registers();
}





void dump_registers() {
  for(uint8_t* pointer = 0x20; pointer < 0xF5; pointer++ ) {
    Serial.print( (uint8_t) pointer, HEX);
    Serial.print(" : ");
    Serial.println(*pointer, BIN);
  }
}

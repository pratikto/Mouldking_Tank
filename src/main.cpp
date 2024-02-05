#include <Arduino.h>
#include <Ps3Controller.h>
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "BDCmotor.h"

#define GPIO_PWM0A_OUT 19   //HV
#define GPIO_PWM1A_OUT 18   //HV
#define GPIO_PWM0B_OUT 17  //LV
#define GPIO_PWM1B_OUT 16  //LV
int freq0 = 50000;
int freq1 = 1000;
float duty0 = 25;
float duty1 = 25;

bool pwm0 = false;
bool pwm1 = false;

void setuppwm(){
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, GPIO_PWM1A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0B, GPIO_PWM0B_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1B, GPIO_PWM1B_OUT);
    mcpwm_config_t pwm_config0;
    pwm_config0.frequency = freq0;  //frequency 
    pwm_config0.cmpr_a = 0;      //duty cycle of PWMxA = 50.0%
    pwm_config0.cmpr_b = 0;      //duty cycle of PWMxB = 50.0%
    pwm_config0.counter_mode = MCPWM_UP_COUNTER; // Up-down counter (triangle wave)
    pwm_config0.duty_mode = MCPWM_DUTY_MODE_0; // Active HIGH
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config0);    //Configure PWM0A & PWM0B with above settings
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config0);    //Configure PWM0A & PWM0B with above settings
    mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_0, &pwm_config0);    //Configure PWM0A & PWM0B with above settings
    mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_1, &pwm_config0);    //
    delay(20);
    mcpwm_set_frequency(MCPWM_UNIT_1, MCPWM_TIMER_1,freq1);
    delay(20);
    mcpwm_set_timer_sync_output(MCPWM_UNIT_0, MCPWM_TIMER_0,MCPWM_SWSYNC_SOURCE_TEZ);
    mcpwm_sync_enable(MCPWM_UNIT_0, MCPWM_TIMER_0,MCPWM_SELECT_TIMER0_SYNC, 0);   
    mcpwm_sync_enable(MCPWM_UNIT_0, MCPWM_TIMER_1,MCPWM_SELECT_TIMER0_SYNC, 500); 
    delay(20);
    mcpwm_set_timer_sync_output(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_SWSYNC_SOURCE_TEZ);
    mcpwm_sync_enable(MCPWM_UNIT_1, MCPWM_TIMER_0,MCPWM_SELECT_TIMER0_SYNC, 0); 
    mcpwm_sync_enable(MCPWM_UNIT_1, MCPWM_TIMER_1,MCPWM_SELECT_TIMER0_SYNC, 500); 
    delay(20);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, duty0);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_A, duty0);
}

int player = 0;
int battery = 0;

void notify()
{
    //--- Digital cross/square/triangle/circle button events ---
    if( Ps3.event.button_down.cross )
        Serial.println("Started pressing the cross button");
    if( Ps3.event.button_up.cross )
        Serial.println("Released the cross button");

    if( Ps3.event.button_down.square )
        Serial.println("Started pressing the square button");
    if( Ps3.event.button_up.square )
        Serial.println("Released the square button");

    if( Ps3.event.button_down.triangle )
        Serial.println("Started pressing the triangle button");
    if( Ps3.event.button_up.triangle )
        Serial.println("Released the triangle button");

    if( Ps3.event.button_down.circle )
        Serial.println("Started pressing the circle button");
    if( Ps3.event.button_up.circle )
        Serial.println("Released the circle button");

    //--------------- Digital D-pad button events --------------
    if( Ps3.event.button_down.up )
        Serial.println("Started pressing the up button");
    if( Ps3.event.button_up.up )
        Serial.println("Released the up button");

    if( Ps3.event.button_down.right )
        Serial.println("Started pressing the right button");
    if( Ps3.event.button_up.right )
        Serial.println("Released the right button");

    if( Ps3.event.button_down.down )
        Serial.println("Started pressing the down button");
    if( Ps3.event.button_up.down )
        Serial.println("Released the down button");

    if( Ps3.event.button_down.left )
        Serial.println("Started pressing the left button");
    if( Ps3.event.button_up.left )
        Serial.println("Released the left button");

    //------------- Digital shoulder button events -------------
    if( Ps3.event.button_down.l1 )
        Serial.println("Started pressing the left shoulder button");
    if( Ps3.event.button_up.l1 )
        Serial.println("Released the left shoulder button");

    if( Ps3.event.button_down.r1 )
        Serial.println("Started pressing the right shoulder button");
    if( Ps3.event.button_up.r1 )
        Serial.println("Released the right shoulder button");

    //-------------- Digital trigger button events -------------
    if( Ps3.event.button_down.l2 )
        Serial.println("Started pressing the left trigger button");
    if( Ps3.event.button_up.l2 )
        Serial.println("Released the left trigger button");

    if( Ps3.event.button_down.r2 )
        Serial.println("Started pressing the right trigger button");
    if( Ps3.event.button_up.r2 )
        Serial.println("Released the right trigger button");

    //--------------- Digital stick button events --------------
    if( Ps3.event.button_down.l3 )
        Serial.println("Started pressing the left stick button");
    if( Ps3.event.button_up.l3 )
        Serial.println("Released the left stick button");

    if( Ps3.event.button_down.r3 )
        Serial.println("Started pressing the right stick button");
    if( Ps3.event.button_up.r3 )
        Serial.println("Released the right stick button");

    //---------- Digital select/start/ps button events ---------
    if( Ps3.event.button_down.select )
        Serial.println("Started pressing the select button");
    if( Ps3.event.button_up.select )
        Serial.println("Released the select button");

    if( Ps3.event.button_down.start )
        Serial.println("Started pressing the start button");
    if( Ps3.event.button_up.start )
        Serial.println("Released the start button");

    if( Ps3.event.button_down.ps )
        Serial.println("Started pressing the Playstation button");
    if( Ps3.event.button_up.ps )
        Serial.println("Released the Playstation button");


    //---------------- Analog stick value events ---------------
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
       Serial.print("Moved the left stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
       Serial.println();
    }

   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
       Serial.print("Moved the right stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
       Serial.println();
   }

   //--------------- Analog D-pad button events ----------------
   if( abs(Ps3.event.analog_changed.button.up) ){
       Serial.print("Pressing the up button: ");
       Serial.println(Ps3.data.analog.button.up, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.right) ){
       Serial.print("Pressing the right button: ");
       Serial.println(Ps3.data.analog.button.right, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.down) ){
       Serial.print("Pressing the down button: ");
       Serial.println(Ps3.data.analog.button.down, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.left) ){
       Serial.print("Pressing the left button: ");
       Serial.println(Ps3.data.analog.button.left, DEC);
   }

   //---------- Analog shoulder/trigger button events ----------
   if( abs(Ps3.event.analog_changed.button.l1)){
       Serial.print("Pressing the left shoulder button: ");
       Serial.println(Ps3.data.analog.button.l1, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.r1) ){
       Serial.print("Pressing the right shoulder button: ");
       Serial.println(Ps3.data.analog.button.r1, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.l2) ){
       Serial.print("Pressing the left trigger button: ");
       Serial.println(Ps3.data.analog.button.l2, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.r2) ){
       Serial.print("Pressing the right trigger button: ");
       Serial.println(Ps3.data.analog.button.r2, DEC);
   }

   //---- Analog cross/square/triangle/circle button events ----
   if( abs(Ps3.event.analog_changed.button.triangle)){
       Serial.print("Pressing the triangle button: ");
       Serial.println(Ps3.data.analog.button.triangle, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.circle) ){
       Serial.print("Pressing the circle button: ");
       Serial.println(Ps3.data.analog.button.circle, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.cross) ){
       Serial.print("Pressing the cross button: ");
       Serial.println(Ps3.data.analog.button.cross, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.square) ){
       Serial.print("Pressing the square button: ");
       Serial.println(Ps3.data.analog.button.square, DEC);
   }

   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( battery == ps3_status_battery_charging )      Serial.println("charging");
        else if( battery == ps3_status_battery_full )     Serial.println("FULL");
        else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
        else if( battery == ps3_status_battery_low)       Serial.println("LOW");
        else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
        else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
        else Serial.println("UNDEFINED");
    }

}

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
  Serial.begin(115200);
  setuppwm();
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("00:26:5c:f0:e9:30");

  //-------------------- Player LEDs -------------------
  Serial.print("Setting LEDs to player "); Serial.println(player, DEC);
  Ps3.setPlayer(player);

  Serial.println("Ready.");
}

void loop()
{
  //PS3 controller disconnect routine
  if(!Ps3.isConnected()){
    ;
    return;
  }
  //PS3 controller connected
  else{
    //--------------- Analog D-pad button events ----------------
    if( abs(Ps3.event.analog_changed.button.up) )
    {
        Serial.print("Pressing the up button: ");
        Serial.println(Ps3.data.analog.button.up, DEC);
    }

   if( abs(Ps3.event.analog_changed.button.right) ){
        Serial.print("Pressing the right button: ");
        Serial.println(Ps3.data.analog.button.right, DEC);
    }

   if( abs(Ps3.event.analog_changed.button.down) ){
       Serial.print("Pressing the down button: ");
       Serial.println(Ps3.data.analog.button.down, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.left) ){
       Serial.print("Pressing the left button: ");
       Serial.println(Ps3.data.analog.button.left, DEC);
   }
  }
}
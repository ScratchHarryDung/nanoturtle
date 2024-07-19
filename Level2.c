void
led_gpio ()
{
  CHIP_Init ();
  USTIMER_Init ();

  while (1)
    {
//      // Do not remove this call: Silicon Labs components process action routine
//      // must be called from the super loop.
//
//      //LED ON/OFF
//
//      // Led blinking
//
      GPIO_PinModeSet (gpioPortC, 1, gpioModePushPull, 1);
      GPIO_PinModeSet (gpioPortC, 2, gpioModePushPull, 1);
      GPIO_PinModeSet (gpioPortC, 3, gpioModePushPull, 1);
      GPIO_PinModeSet (gpioPortC, 0, gpioModePushPull, 1); //buzzer
//
      USTIMER_Delay (500000);
//
      GPIO_PinModeSet (gpioPortC, 1, gpioModePushPull, 0);
      GPIO_PinModeSet (gpioPortC, 2, gpioModePushPull, 0);
      GPIO_PinModeSet (gpioPortC, 3, gpioModePushPull, 0);
//
      USTIMER_Delay (500000);
    }
}
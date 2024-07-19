#include "sl_status.h"
#include "sl_sleeptimer.h"
#include "app_log.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_adc.h"
#include "mikroe_mq7.h"
#include "ustimer.h"

#define READING_INTERVAL_MSEC 3000

static volatile bool timer_is_expire = false;
static sl_sleeptimer_timer_handle_t app_timer_handle;

static void app_timer_cb(sl_sleeptimer_timer_handle_t *handle, void *data);

void app_init(void)
{
  if (mikroe_mq7_init(IADC0) == SL_STATUS_OK) {
    app_log("Initialize CO sensor successfully\n");

    sl_sleeptimer_start_periodic_timer(&app_timer_handle,
                                       READING_INTERVAL_MSEC,
                                       app_timer_cb,
                                       (void *) NULL,
                                       0,
                                       0);
  }
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}

static void app_timer_cb(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void) handle;
  (void) data;

  timer_is_expire = true;
}



void sensorinit(void) {
  mikroe_mq7_init(IADC0);
  mikroe_mq7_set_adc_instance(IADC0);
}


void adclog(void) {
  float value;
  uint16_t data_out;

  if (timer_is_expire == true) {
    timer_is_expire = false;

    if (mikroe_mq7_read_an_pin_value(&data_out) == SL_STATUS_OK) {
      app_log("PPM Value: %d\n", data_out);
    } else {
      app_log("Fail to read\n");
    }

    if (data_out <= 200) {
      // Turn on the buzzer
        GPIO_PinModeSet (gpioPortC, 0, gpioModePushPull, 1);
        GPIO_PinModeSet (gpioPortC, 1, gpioModePushPull, 0);
        GPIO_PinModeSet (gpioPortC, 2, gpioModePushPull, 0);
        GPIO_PinModeSet (gpioPortC, 3, gpioModePushPull, 0);
    } else if (data_out >= 201){
      // Turn off the buzzer
        GPIO_PinModeSet (gpioPortC, 0, gpioModePushPull, 0);
        GPIO_PinModeSet (gpioPortC, 1, gpioModePushPull, 1);
        GPIO_PinModeSet (gpioPortC, 2, gpioModePushPull, 0);
        GPIO_PinModeSet (gpioPortC, 3, gpioModePushPull, 1);
    } else if (data_out >= 1000){
    // Turn off the buzzer
        GPIO_PinModeSet (gpioPortC, 0, gpioModePushPull, 0);
        GPIO_PinModeSet (gpioPortC, 1, gpioModePushPull, 0);
        GPIO_PinModeSet (gpioPortC, 2, gpioModePushPull, 1);
        GPIO_PinModeSet (gpioPortC, 3, gpioModePushPull, 1);

  }
  }
}

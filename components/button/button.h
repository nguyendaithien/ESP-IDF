/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Ruslan V. Uss <unclerus@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file button.h
 * @defgroup button button
 * @{
 *
 * ESP-IDF driver for simple GPIO buttons.
 *
 * Supports anti-jitter, auto repeat, long press.
 *
 * Copyright (c) 2021 Ruslan V. Uss <unclerus@gmail.com>
 *
 * MIT Licensed as described in the file LICENSE
 */
#ifndef __BUTTON_H__
#define __BUTTON_H__
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"


#include "esp_log.h"
#include "esp_system.h"

#include "esp_netif.h"
#include "esp_smartconfig.h"

#include "esp_event.h"
#include "button.h"

#include <stdint.h>
#include <stdbool.h>
#include <driver/gpio.h>
#include <esp_err.h>
#include <esp_timer.h>
#include <sdkconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Typedef of button descriptor
 */
typedef struct button_s button_t;
#define CONFIG_BUTTON_POLL_TIMEOUT 10
#define CONFIG_BUTTON_LONG_PRESS_TIMEOUT 1000
#define CONFIG_BUTTON_AUTOREPEAT_TIMEOUT 500
#define CONFIG_BUTTON_AUTOREPEAT_INTERVAL 250
#define CONFIG_BUTTON_MAX 5

#define button_1 35
/**
 * Button states/events
 */
//bool check_button_n( button_t *btn);
bool button_press( uint8_t button);
void poll_button(button_t *btn);
int button_time( uint8_t,int);
void in( void);
bool longPress( uint8_t button);
bool check_button_n( uint8_t button , int n);
typedef enum {
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED,
    BUTTON_CLICKED,
    BUTTON_PRESSED_LONG,
} button_state_t;

/**
 * Callback prototype
 *
 * @param btn    Pointer to button descriptor
 * @param state  Button action (new state)
 */
typedef void (*button_event_cb_t)(button_t *btn, button_state_t state);

/**
 * Button descriptor struct
 */
struct button_s
{
    gpio_num_t gpio;                //!< GPIO
    bool internal_pull;             //!< Enable internal pull-up/pull-down
    uint8_t pressed_level;          //!< Logic level of pressed button
    bool autorepeat;                //!< Enable autorepeat
    button_event_cb_t callback;     //!< Button callback
    void *ctx;                      //!< User data
    struct {
        button_state_t state;
        int pressed_time;
        uint32_t repeating_time;
    } internal;                     //!< Internal button state
};

/**
 * @brief Init button
 *
 * @param btn Pointer to button descriptor
 * @return `ESP_OK` on success
 */
esp_err_t button_init(button_t *btn);

/**
 * @brief Deinit button
 *
 * @param btn Pointer to button descriptor
 * @return `ESP_OK` on success
 */
esp_err_t button_done(button_t *btn);

#ifdef __cplusplus
}
#endif

#endif
/**@}*/


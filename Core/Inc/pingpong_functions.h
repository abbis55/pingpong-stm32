#ifndef PINGPONG_FUNCTIONS_H_
#define PINGPONG_FUNCTIONS_H_

/**
 * @file    pingpong_functions.h
 * @brief   API för Pingpong-funktioner (LED + knappar)
 * @details Deklarationer för funktionsbiblioteket som används av test- och spelkod.
 */

#include "main.h"   // ger LEDx_Pin och LEDx_GPIO_Port
#include <stdbool.h>

bool L_hit(void);
bool R_hit(void);


#ifdef __cplusplus
extern "C" {
#endif

/** Släck alla åtta LED */
void All_leds_off(void);

/** Tänd exakt en LED (1–8). Ogiltigt värde → släck alla. */
void Led_on(uint8_t lednr);

/** Släck en specifik LED (1–8). Ogiltigt värde → gör inget. */
void Led_off(uint8_t lednr);

/** Hjälpfunktion: tänd LED n och släck övriga (alias till Led_on). */
static inline void Led_only(uint8_t n) { Led_on(n); }

/** Läs vänster/höger knapp (retur: 1=tryckt, 0=släppt) */
uint8_t L_button_pressed(void);
uint8_t R_button_pressed(void);

void Show_points(uint8_t L_points, uint8_t R_points);


#ifdef __cplusplus
}
#endif

#endif /* PINGPONG_FUNCTIONS_H_ */

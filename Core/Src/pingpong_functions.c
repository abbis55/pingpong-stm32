/**
 ******************************************************************************
 * @file    pingpong_functions.c
 * @brief   Functions used in the Pingpong program
 * @author  Albert
 * @version 1.0
 * @date    2025-11-07
 * @details Contains LED control functions for the Pingpong assignment
 ******************************************************************************
 */

#include "Pingpong.h"   // bör i sin tur inkludera "main.h"
#include "pingpong_functions.h"
#include <stdbool.h>
#include "main.h"      // <-- ger L_button_Pin, L_button_GPIO_Port etc.
#include <stdbool.h>
extern volatile bool L_flag;
extern volatile bool R_flag;

/**
 * @brief Släck alla åtta LED.
 */
void All_leds_off(void)
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
}

void Led_on(uint8_t Lednr) {
	uint8_t i;
	for (i = 1; i <= 8; i++) {
		switch (i) {
		case 1:  // Led 1
			if (Lednr == i)
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
			break;
		case 2:  // Led 2
			if (Lednr == i)
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
			break;
		case 3:  // Led 3
			if (Lednr == i)
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
			break;
		case 4:  // Led 4
			if (Lednr == i)
				HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
			break;
		case 5:  // Led 5
			if (Lednr == i)
				HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
			break;
		case 6:  // Led 6
			if (Lednr == i)
				HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
			break;
		case 7:  // Led 7
			if (Lednr == i)
				HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
			break;
		case 8:  // Led 8
			if (Lednr == i)
				HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
			break;
		default:
			;
		}
		// end switch
	} // end for-loop
	return;
} // End of function Led_on

/**
 * @brief Släck en specifik LED (1–8). Ogiltigt värde → gör inget.
 */
void Led_off(uint8_t lednr)
{
    switch (lednr) {
        case 1: HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET); break;
        case 2: HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); break;
        case 3: HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET); break;
        case 4: HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET); break;
        case 5: HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET); break;
        case 6: HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET); break;
        case 7: HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET); break;
        case 8: HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET); break;
        default: break;
    }
}

///**
// * @brief Läs vänster knapp (aktiv låg: tryckt = 1).
// */
//uint8_t L_button_pressed(void)
//{
//    return (HAL_GPIO_ReadPin(L_button_GPIO_Port, L_button_Pin) == GPIO_PIN_RESET) ? 1u : 0u;
//}
//
///**
// * @brief Läs höger knapp (aktiv låg: tryckt = 1).
// */
//uint8_t R_button_pressed(void)
//{
//    return (HAL_GPIO_ReadPin(R_button_GPIO_Port, R_button_Pin) == GPIO_PIN_RESET) ? 1u : 0u;
//}

// Hjälpare: skriv till valfri LED 1..8 (SET/RESET)
static void led_write(uint8_t idx, GPIO_PinState s)
{
    switch (idx) {
        case 1: HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, s); break;
        case 2: HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, s); break;
        case 3: HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, s); break;
        case 4: HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, s); break;
        case 5: HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, s); break;
        case 6: HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, s); break;
        case 7: HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, s); break;
        case 8: HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, s); break;
        default: break;
    }
}

/**
 * @brief  Visa poäng efter missad boll.
 *         Blinkar alla LED kort (0,1 s), visar sedan poängen i 1 s.
 *         Vänster: tänd från LED1 in mot mitten (1..4).
 *         Höger:  tänd från LED8 in mot mitten (8..5).
 * @param  L_points  (0..4)
 * @param  R_points  (0..4)
 */
void Show_points(uint8_t L_points, uint8_t R_points)
{
    if (L_points > 4) L_points = 4;
    if (R_points > 4) R_points = 4;

    // 1) Blink alla kort (0,1 s)
    for (uint8_t i = 1; i <= 8; ++i) led_write(i, GPIO_PIN_SET);
    HAL_Delay(400);
    for (uint8_t i = 1; i <= 8; ++i) led_write(i, GPIO_PIN_RESET);

    // 2) Visa poängen
    // Släck allt först (tydligt läge)
    for (uint8_t i = 1; i <= 8; ++i) led_write(i, GPIO_PIN_RESET);

    // Vänster: LED1..LED4 (ytterkant in mot mitten)
    for (uint8_t i = 1; i <= L_points; ++i) {
        led_write(i, GPIO_PIN_SET);
    }
    // Höger: LED8..LED5 (ytterkant in mot mitten)
    for (uint8_t k = 0; k < R_points; ++k) {
        led_write(8 - k, GPIO_PIN_SET);   // 8,7,6,5
    }

    HAL_Delay(1000);   // visa i 1 s

    // Släck efter visning (valfritt – smidigt inför nästa sekvens)
    for (uint8_t i = 1; i <= 8; ++i) led_write(i, GPIO_PIN_RESET);
}


// Aktiv låg: tryckt = 0V = GPIO_PIN_RESET
//bool L_hit(void)
//{
//    return (HAL_GPIO_ReadPin(L_button_GPIO_Port, L_button_Pin) == GPIO_PIN_RESET);
//}
//
//bool R_hit(void)
//{
//    return (HAL_GPIO_ReadPin(R_button_GPIO_Port, R_button_Pin) == GPIO_PIN_RESET);
//}


//interrupt
bool L_hit(void)
{
#ifdef USE_INTERRUPT_BUTTONS
    if (L_flag) { L_flag = false; return true; }
    return false;
#else
    return (HAL_GPIO_ReadPin(L_button_GPIO_Port, L_button_Pin) == GPIO_PIN_RESET);
#endif
}

bool R_hit(void)
{
#ifdef USE_INTERRUPT_BUTTONS
    if (R_flag) { R_flag = false; return true; }
    return false;
#else
    return (HAL_GPIO_ReadPin(R_button_GPIO_Port, R_button_Pin) == GPIO_PIN_RESET);
#endif
}


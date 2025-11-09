#include "Test.h"
#include "pingpong_functions.h"

static void Test_buttons(void);   // <-- prototyp före Test_program

//void Test_program(void)
//{
//    Test_Led();        // prototypen finns i Test.h → inga “implicit” varningar
//    while (1) { }
//}
//
//void Test_Led(void)
//{
//    int8_t Lednr;
//    for (Lednr = 1; Lednr <= 8; Lednr++) {
//        Led_on(Lednr);
//        HAL_Delay(500);
//    }
//    Led_on(9);         // i din Led_on släcks alla vid ogiltigt nr
//    HAL_Delay(1000);
//}
/**
 * @brief  Test-program: tänd LED 1..8 i tur och ordning, släck sedan alla.
 */
//void Test_program(void)
//{
//    for (uint8_t i = 1; i <= 8; ++i) {
//        Led_on(i);
//        HAL_Delay(200);
//    }
//    Led_on(9); // ogiltigt tal → släck alla enligt vår policy
//    HAL_Delay(500);
//
//    while (1) {
//        // enkel knapp-demonstration
//        if (L_button_pressed()) { Led_on(1); }
//        if (R_button_pressed()) { Led_on(8); }
//        HAL_Delay(50);
//    }
//}
static void Test_Show_points(void) {
	for (uint8_t L = 1; L <= 4; ++L) {
		for (uint8_t R = 1; R <= 4; ++R) {
			Show_points(L, R);
			HAL_Delay(300); // liten paus mellan visningar
		}
	}
}

void Test_program(void) {
	// Kör testet i en loop så du kan titta på alla kombinationer
	while (1) {
		//Test_Show_points();
		Test_buttons();
	}
}

void Test_buttons(void) {
	int8_t j;
	/* Checking buttons */
	j = 4;
	Led_on(j); // Light on
	while (j < 9 && j > 0) {
		if (L_hit() == true) // Wait for left button hit
		{
			j++;
// next led to the right
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while (L_hit() == true)
				; // Wait for button release
			HAL_Delay(100); // 100 ms
		}
		if (R_hit() == true) // Wait for right button hit
		{
			j--;
// next led to the left
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while (R_hit() == true)
				; // Wait for button release
			HAL_Delay(100); // 100 ms
			if (j < 1)
				j = 0; // Start again from left
		}
	}
	return;
}


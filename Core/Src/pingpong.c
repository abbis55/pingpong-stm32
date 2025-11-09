/*
 * pingpong.c
 *
 *  Created on: Nov 7, 2025
 *      Author: alber
 */
#include "Pingpong.h"
#include "pingpong_functions.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

// --- Tillstånd ---
typedef enum {
    Start,
    MoveRight,
    MoveLeft
} State_t;

static State_t State, NextState;

// Konfiguration
static const uint32_t SPEED_START_MS = 250;  // start-hastighet (ms per steg)
static const uint32_t SPEED_MIN_MS   = 80;   // snabbaste hastighet
static const uint32_t SPEED_STEP_MS  = 15;   // hur mycket vi snabbar på per retur
static const uint8_t  MAX_POINTS     = 4;

// Hjälpare: vänta 'ms' och kolla knapp för vald sida
static bool wait_ms_and_check_press(uint32_t ms, bool checkLeft)
{
    uint32_t t0 = HAL_GetTick();
    while ((HAL_GetTick() - t0) < ms) {
        if (checkLeft) {
            if (L_hit()) return true;
        } else {
            if (R_hit()) return true;
        }
    }
    return false;
}

void Pingpong(void)
{
    uint8_t  Led = 0;                // aktuell LED (1..8), 0 eller 9 = miss
    uint32_t speed_ms = SPEED_START_MS;
    uint8_t  L_points = 0, R_points = 0;
    bool     ButtonPressed = false;

    // Vem servar? 0 = valfritt (första), därefter växlar vi
    bool nextServeLeft = true;

    State = Start;
    NextState = Start;

    for(;;)
    {
        State = NextState;

        switch (State)
        {
        case Start:
            // Släck allt och vänta på serve (valfri sida första gången, sedan alternerande)
            Led_on(0);

            // Visa vems serve (frivilligt): tänd svagt ytter-LED? (skippa om du vill)
            // Här räcker det att vänta på knapp:
            if (nextServeLeft) {
                if (L_hit()) { Led = 1; NextState = MoveRight; while (L_hit()); }
                else if (R_hit()) { Led = 8; NextState = MoveLeft; while (R_hit()); }
                else { NextState = Start; }
            } else {
                if (R_hit()) { Led = 8; NextState = MoveLeft; while (R_hit()); }
                else if (L_hit()) { Led = 1; NextState = MoveRight; while (L_hit()); }
                else { NextState = Start; }
            }

            // återställ hastighet vid ny serve
            speed_ms = SPEED_START_MS;
            break;

        case MoveRight:
            // Tänd aktuell LED och vänta 'speed_ms'; under tiden lyssna på höger knapp
            Led_on(Led);
            ButtonPressed = wait_ms_and_check_press(speed_ms, /*checkLeft=*/false);

            if (ButtonPressed) {
                // R tryckte – bara OK om bollen är längst till höger (LED8)
                if (Led == 8) {
                    // retur → vänd riktning, gå ett steg inåt
                    NextState = MoveLeft;
                    Led = 7;
                    // snabba upp lite
                    if (speed_ms > SPEED_MIN_MS + SPEED_STEP_MS) speed_ms -= SPEED_STEP_MS;
                } else {
                    // för tidigt → poäng till L
                    L_points++;
                    Show_points(L_points, R_points);
                    if (L_points >= MAX_POINTS) {
                        HAL_Delay(5000);
                        L_points = R_points = 0;
                    }
                    nextServeLeft = false; // efter poäng: andra spelaren servar
                    NextState = Start;
                }
            } else {
                // ingen tryckning – bollen vandrar vidare
                if (Led >= 8) {
                    // miss (för sent) → poäng till L
                    L_points++;
                    Show_points(L_points, R_points);
                    if (L_points >= MAX_POINTS) {
                        HAL_Delay(5000);
                        L_points = R_points = 0;
                    }
                    nextServeLeft = false;
                    NextState = Start;
                } else {
                    Led++;               // vandra ett steg
                    NextState = MoveRight;
                }
            }
            break;

        case MoveLeft:
            // Tänd aktuell LED och vänta; lyssna på vänster knapp
            Led_on(Led);
            ButtonPressed = wait_ms_and_check_press(speed_ms, /*checkLeft=*/true);

            if (ButtonPressed) {
                // L tryckte – bara OK om bollen är längst till vänster (LED1)
                if (Led == 1) {
                    NextState = MoveRight;
                    Led = 2;
                    if (speed_ms > SPEED_MIN_MS + SPEED_STEP_MS) speed_ms -= SPEED_STEP_MS;
                } else {
                    // för tidigt → poäng till R
                    R_points++;
                    Show_points(R_points < 10 ? L_points : L_points, R_points);
                    if (R_points >= MAX_POINTS) {
                        HAL_Delay(5000);
                        L_points = R_points = 0;
                    }
                    nextServeLeft = true;
                    NextState = Start;
                }
            } else {
                // ingen tryckning – bollen vandrar vidare
                if (Led <= 1) {
                    // miss (för sent) → poäng till R
                    R_points++;
                    Show_points(L_points, R_points);
                    if (R_points >= MAX_POINTS) {
                        HAL_Delay(5000);
                        L_points = R_points = 0;
                    }
                    nextServeLeft = true;
                    NextState = Start;
                } else {
                    Led--;
                    NextState = MoveLeft;
                }
            }
            break;

        default:
            NextState = Start;
            break;
        }
    }
}

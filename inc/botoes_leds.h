#ifndef BOTOES_LEDS_H
#define BOTOES_LEDS_H

#include "pico/stdlib.h"

// Definições dos pinos
#define BUTTON_A 5
#define BUTTON_B 6
#define LED_GREEN 11
#define LED_BLUE 12

// Declarações das variáveis globais
extern bool buttonA_last_state;
extern bool buttonB_last_state;

// Declarações das funções
void inicializar_botoes_leds();
void atualizar_leds(bool led_green_state, bool led_blue_state);
bool ler_botao_a();
bool ler_botao_b();

#endif // BOTOES_LEDS_H
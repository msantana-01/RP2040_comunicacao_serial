#ifndef MATRIZ_LEDS_H
#define MATRIZ_LEDS_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// Definições da matriz de LEDs
#define PINO_LED 7         // Pino da matriz de LEDs
#define NUMERO_LEDS 25     // Total de LEDs na matriz

// Estrutura para representar um pixel RGB
struct pixel_t
{
    uint8_t verde, vermelho, azul;
};

// Declaração das funções
void inicializar_leds(uint pino);
void definir_led(uint indice, uint8_t vermelho, uint8_t verde, uint8_t azul, uint8_t intensidade);
void escrever_leds();
void limpar_leds();
void exibir_numero(int numero);

#endif // MATRIZ_LEDS_H
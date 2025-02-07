#include "matriz_leds.h"
#include "ws2818b.pio.h"

// Matriz de LEDs 5x5
const uint8_t MATRIZ_LEDS[5][5] = {
    {24, 23, 22, 21, 20},
    {15, 16, 17, 18, 19},
    {14, 13, 12, 11, 10},
    {5, 6, 7, 8, 9},
    {4, 3, 2, 1, 0}};

// Padrões dos números (0-9) para a matriz 5x5
// 1 representa LED aceso, 0 representa LED apagado
const uint8_t PADROES_NUMEROS[10][5][5] = {
    {// 0
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}},
    {// 1
     {0, 1, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 1, 1, 1, 0}},
    {// 2
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1}},
    {// 3
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}},
    {// 4
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1}},
    {// 5
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}},
    {// 6
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}},
    {// 7
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 1, 0},
     {0, 0, 1, 0, 0},
     {0, 1, 0, 0, 0}},
    {// 8
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}},
    {// 9
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}},
};

// Variáveis globais
struct pixel_t leds[NUMERO_LEDS];
PIO pio = pio0;
uint maquina_estados;

// Funções de inicialização dos LEDs WS2812
void inicializar_leds(uint pino)
{
    uint offset = pio_add_program(pio0, &ws2818b_program);
    pio = pio0;
    maquina_estados = pio_claim_unused_sm(pio, false);
    if (maquina_estados < 0)
    {
        pio = pio1;
        maquina_estados = pio_claim_unused_sm(pio, true);
    }
    ws2818b_program_init(pio, maquina_estados, offset, pino, 800000.f);

    for (uint i = 0; i < NUMERO_LEDS; ++i)
    {
        leds[i].vermelho = 0;
        leds[i].verde = 0;
        leds[i].azul = 0;
    }
}

void definir_led(uint indice, uint8_t vermelho, uint8_t verde, uint8_t azul, uint8_t intensidade)
{
    // Aplica a intensidade (ajusta o valor de vermelho, verde e azul)
    leds[indice].vermelho = (vermelho * intensidade) / 255;
    leds[indice].verde = (verde * intensidade) / 255;
    leds[indice].azul = (azul * intensidade) / 255;
}

void escrever_leds()
{
    for (uint i = 0; i < NUMERO_LEDS; ++i)
    {
        pio_sm_put_blocking(pio, maquina_estados, leds[i].verde);
        pio_sm_put_blocking(pio, maquina_estados, leds[i].vermelho);
        pio_sm_put_blocking(pio, maquina_estados, leds[i].azul);
    }
}

void limpar_leds()
{
    for (uint i = 0; i < NUMERO_LEDS; ++i)
    {
        definir_led(i, 0, 0, 0, 0);
    }
    escrever_leds();
}

// Função para exibir número na matriz
void exibir_numero(int numero)
{
    limpar_leds();
    if (numero < 0 || numero > 9)
        return;

    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            if (PADROES_NUMEROS[numero][linha][coluna])
            {
                uint8_t indice_led = MATRIZ_LEDS[linha][coluna];
                definir_led(indice_led, 0, 0, 255, 200);
                sleep_us(50); // Atraso para evitar problemas de temporização
            }
        }
    }
    escrever_leds();
}
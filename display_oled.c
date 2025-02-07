// #include "inc/ssd1306.h"
#include "inc/font.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "inc/matriz_leds.h"
#include "inc/botoes_leds.h"
#include "inc/display.h" 
#define TEMPO_DEBOUNCE 200 // Tempo de debounce em ms

uint32_t ultimo_tempo_botao = 0;

int main()
{
    stdio_init_all();

    // Configura o display
    ssd1306_t ssd;
    init_display(&ssd);

    // Inicializa botões e LEDs
    inicializar_botoes_leds();

    // Inicializa a matriz de LEDs
    inicializar_leds(PINO_LED);

    // Limpa a matriz de LEDs ao iniciar o programa
    limpar_leds();

    // Variáveis para o estado dos LEDs
    bool led_green_state = false;
    bool led_blue_state = false;

    while (true)
    {
        // Captura caractere do teclado sem bloquear a execução
        int ch = getchar_timeout_us(0);
        if (ch != PICO_ERROR_TIMEOUT)
        {
            char c = (char)ch;
            char message[2] = {c, '\0'};
            display_message(&ssd, "Caractere", message); // Exibe no display
            printf("Caracter digitado: %c\n", c);        // Exibe no terminal

            // Verifica se o caractere é um número entre 0 e 9
            if (c >= '0' && c <= '9')
            {
                int numero = c - '0';  // Converte o caractere para um número
                exibir_numero(numero); // Exibe o número na matriz de LEDs
            }
        }

        // Lê estados atuais dos botões
        bool buttonA_state = ler_botao_a();
        bool buttonB_state = ler_botao_b();

        if (buttonA_last_state == true && buttonA_state == false)
        {
            if (debounce(&ultimo_tempo_botao, TEMPO_DEBOUNCE))
            {
                led_green_state = !led_green_state; // Alterna o estado do LED verde

                // Desliga o LED azul se o LED verde for ligado
                if (led_green_state)
                {
                    led_blue_state = false;
                }

                atualizar_leds(led_green_state, led_blue_state);
                printf("LED Verde %s\n", led_green_state ? "Ligado" : "Desligado");
                display_message(&ssd, "LED Verde", led_green_state ? "Ligado" : "Desligado");
            }
        }

        if (buttonB_last_state == true && buttonB_state == false)
        {
            if (debounce(&ultimo_tempo_botao, TEMPO_DEBOUNCE))
            {
                led_blue_state = !led_blue_state; // Alterna o estado do LED azul

                // Desliga o LED verde se o LED azul for ligado
                if (led_blue_state)
                {
                    led_green_state = false;
                }

                atualizar_leds(led_green_state, led_blue_state);
                printf("LED Azul %s\n", led_blue_state ? "Ligado" : "Desligado");
                display_message(&ssd, "LED Azul", led_blue_state ? "Ligado" : "Desligado");
            }
        }

        // Atualiza o estado anterior dos botões
        buttonA_last_state = buttonA_state;
        buttonB_last_state = buttonB_state;

        sleep_ms(10);
    }

    return 0;
}
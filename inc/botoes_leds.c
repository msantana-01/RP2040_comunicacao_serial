#include "botoes_leds.h"
#include "pico/time.h"

// Definições das variáveis globais
bool buttonA_last_state = true;
bool buttonB_last_state = true;

void inicializar_botoes_leds() {
    // Configura botões
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // Configura LEDs
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);
}

void atualizar_leds(bool led_green_state, bool led_blue_state) {
    gpio_put(LED_GREEN, led_green_state);
    gpio_put(LED_BLUE, led_blue_state);
}

bool ler_botao_a() {
    return gpio_get(BUTTON_A);
}

bool ler_botao_b() {
    return gpio_get(BUTTON_B);
}

bool debounce(uint32_t *ultimo_tempo, uint32_t tempo_debounce) {
    uint32_t agora = to_ms_since_boot(get_absolute_time());
    if (agora - *ultimo_tempo >= tempo_debounce) {
        *ultimo_tempo = agora;
        return true;
    }
    return false;
}
# Controle de LEDs com Matriz e Display OLED - Raspberry Pi Pico W

Este projeto utiliza um Raspberry Pi Pico W para controlar LEDs, exibir números em uma matriz de LEDs e mostrar informações em um display OLED SSD1306. A interação é feita por meio de dois botões que alternam entre o estado de LEDs verdes e azuis. A entrada de caracteres também é exibida no display OLED.

## Funcionalidades

- **Matriz de LEDs**: Exibe números de 0 a 9 conforme pressionado.
- **Display OLED SSD1306**: Mostra a entrada de caracteres e o estado dos LEDs.
- **Botões A e B**:
  - O botão A alterna o estado do LED verde.
  - O botão B alterna o estado do LED azul.
- **Debounce**: Garantia de um tempo de debounce de 200ms para evitar leituras incorretas dos botões.

## Requisitos

- Raspberry Pi Pico W.
- Matriz de LEDs WS2812B.
- Display OLED SSD1306.
- Botões para interação.

## Materiais

- **Raspberry Pi Pico W**.
- **Matriz de LEDs WS2812B** conectada ao GPIO 7.
- **Display OLED SSD1306** conectado via I2C.
- **Botão A** no GPIO 5 e **Botão B** no GPIO 6.
- **Buzzer** no GPIO 21 (opcional).

## Instalação

1. **Configuração do Raspberry Pi Pico W**:
   - Baixe e instale o [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk).
   - Clone este repositório e compile o código com o SDK.

2. **Conexões**:
   - **Matriz de LEDs**: Conecte os pinos da matriz aos pinos GPIO do Pico.
   - **Display OLED SSD1306**: Conecte o display via I2C.
   - **Botões A e B**: Conecte ao GPIO 5 e GPIO 6.

3. **Compilação e Upload**:
   - Compile o código usando o SDK.
   - Carregue o binário para o seu Raspberry Pi Pico W.

## Uso

- **Entradas**: Quando você pressiona o botão A, o LED verde alterna seu estado. Quando o botão B é pressionado, o LED azul alterna.
- **Exibição no Display OLED**: O caractere digitado no terminal será exibido no display OLED. Se o caractere for um número entre 0 e 9, o número também será exibido na matriz de LEDs.

## Estrutura do Código

1. **Configuração Inicial**:
   - Inicializa o display OLED.
   - Configura os botões e a matriz de LEDs.
   - Limpa a matriz de LEDs ao iniciar.

2. **Loop Principal**:
   - Monitora a entrada do teclado e a pressão dos botões.
   - Atualiza o estado dos LEDs e exibe a informação no display.

3. **Debounce**:
   - Evita leituras incorretas dos botões com um tempo de debounce de 200ms.

## Exemplos de Comandos

1. Pressione o botão A para alternar o LED verde.
2. Pressione o botão B para alternar o LED azul.
3. Digite um número no terminal para exibi-lo na matriz de LEDs.

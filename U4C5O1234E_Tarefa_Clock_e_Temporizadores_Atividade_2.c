#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos dos LEDs
#define LED_VERDE    11
#define LED_AZUL     12
#define LED_VERMELHO 13
#define BOTAO_PIN    5  // Pino do botão (GPIO 5)

// Variáveis de controle
volatile int estado = 0;        // Estado atual do semáforo
volatile bool ciclo_ativo = false; // Indica se o ciclo está rodando

// Função de callback do temporizador para mudar o estado do semáforo
bool mudar_estado_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de ativar o próximo estado
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);

    // Alterna entre os estados
    switch (estado) {
        case 0:  // Todos os LEDs ligados
            gpio_put(LED_VERDE, 1);
            gpio_put(LED_AZUL, 1);
            gpio_put(LED_VERMELHO, 1);
            printf("Estado 0: Todos acesos - luz branca\n");
            estado = 1;
            break;
        case 1:  // Apenas vermelho e verde acesos
            gpio_put(LED_VERDE, 1);
            gpio_put(LED_VERMELHO, 1);
            printf("Estado 1: Vermelho e Verde - luz amarela\n");
            estado = 2;
            break;
        case 2:  // Apenas verde aceso
            gpio_put(LED_VERDE, 1);
            printf("Estado 2: Verde\n");
            estado = 3;
            break;
        case 3:  // Todos os LEDs desligados e finaliza o ciclo
            printf("Estado 3: Todos apagados\n");
            ciclo_ativo = false; // Permite um novo acionamento pelo botão
            return false;  // Para o temporizador
    }

    return true; // Continua chamando o callback a cada 3 segundos
}

// Função de callback para imprimir o status do semáforo a cada 1 segundo
bool imprimir_status_callback(struct repeating_timer *t) {
    if (ciclo_ativo) {
        printf("Semáforo em execução...\n");
    }
    return true; // Continua chamando o callback a cada 1 segundo
}

// Função para detectar pressionamento do botão (com debounce)
bool botao_pressionado() {
    if (gpio_get(BOTAO_PIN) == 0) {
        sleep_ms(50);  // Debounce de 50ms
        return gpio_get(BOTAO_PIN) == 0;
    }
    return false;
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    printf("Inicializando semáforo...\n");  // Teste de início

    // Configura os LEDs como saída
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    // Configura o pino do botão como entrada com pull-up
    gpio_init(BOTAO_PIN);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_PIN);

    struct repeating_timer timer_estado;
    struct repeating_timer timer_status;

    // Inicia o temporizador para o status a cada 1 segundo
    add_repeating_timer_ms(1000, imprimir_status_callback, NULL, &timer_status);

    while (true) {
        printf("Loop principal rodando...\n");  // Teste no loop principal
        // Inicia o ciclo quando o botão for pressionado
        if (!ciclo_ativo && botao_pressionado()) {
            printf("Botão pressionado! Iniciando ciclo do semáforo...\n");

            // Ativa todos os LEDs inicialmente
            gpio_put(LED_VERDE, 1);
            gpio_put(LED_AZUL, 1);
            gpio_put(LED_VERMELHO, 1);

            ciclo_ativo = true;
            estado = 1; // Prepara para o próximo estado

            // Inicia o temporizador para mudar o estado do semáforo
            add_repeating_timer_ms(1000, mudar_estado_callback, NULL, &timer_estado);
        }

        sleep_ms(10); // Pequena espera para evitar alto uso da CPU
    }

    return 0; // Nunca será alcançado
}

🚦 Controle de Semáforo com Raspberry Pi Pico

Este projeto implementa um sistema de controle de semáforo utilizando um Raspberry Pi Pico e LEDs. O semáforo muda de estado automaticamente a cada 3 segundos após o acionamento de um botão.
📌 Requisitos

    Placa: Raspberry Pi Pico / BitDogLab
    Linguagem: C
    Bibliotecas:
        pico/stdlib.h
        pico/time.h
    Hardware:
        3 LEDs: Vermelho (GPIO 13), Azul (GPIO 12), Verde (GPIO 11)
        1 Botão para iniciar o ciclo (GPIO 5)
        Resistores de pull-up para o botão (se necessário)

⚙️ Funcionalidades

✅ Botão para iniciar o ciclo
✅ Mudança de estados a cada 3 segundos
✅ Estados do semáforo:

    Todos os LEDs ligados
    Vermelho e Verde acesos
    Somente Verde aceso
    Todos desligados (fim do ciclo)
    ✅ Botão com debounce
    ✅ Ciclo só reinicia ao pressionar o botão novamente

🚀 Como Executar

    Conectar os LEDs e o botão conforme os pinos especificados.
    Compilar e carregar o código no Raspberry Pi Pico usando um ambiente como o Pico SDK.
    Executar o programa e pressionar o botão para iniciar o ciclo do semáforo.

🎥 Vídeo de Simulação

🔗 [Assista ao vídeo da simulação aqui](https://github.com/alinemach/U4C5O1234E_Tarefa_Clock_e_Temporizadores_Atividade_2/blob/main/src/atividade2_explicada.mp4)

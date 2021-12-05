# Microcontrolador_PIC_18F4555_Projeto5
Uso de Interrupção externa + Temporizador 0 + LCD no microcontrolador PIC 18F4555

Atividade desenvolvida na disciplina Microprocessadores e Microcontroladores da minha graduação em Engenharia de Computação.

Neste programa,  interrupção externa 0 é usada para aumentar o período de uma onda quadrada de 100 em 100 ms, até o limite de 900 ms e a interrupção externa 2 é usada par diminuir o período da onda quadrada de 100 em 100 ms, até o limite mínimo de 100 ms. A onda quadrada deve ser gerada pelo Temporizador 0 e mostrada no pino D0. Na primeira linha do LCD deve ser mostrada a mensagem “ Onda Quadrada ”; na segunda linha deve ser mostrada a mensagem: “Periodo: xxx ms”, onde “xxx” é o período em ms.

Para compilar o código, recomenda-se o uso da IDE MPLab-X https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide

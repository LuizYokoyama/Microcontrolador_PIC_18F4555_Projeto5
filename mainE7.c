/* 
 * File:   main.c
 * Author: Luiz Felix
 *
 * Created on 14 de Dezembro de 2020, 12:52
 */
#define _XTAL_FREQ 4000000
#include <stdio.h>
#include <xc.h>
#define RS LATD2 // < Pinos do LCD
#define EN LATD3
#define D4 LATD4
#define D5 LATD5
#define D6 LATD6
#define D7 LATD7
#include "lcd.h"
#pragma config FOSC = HS // Oscilador externo
#pragma config WDT = OFF // Watchdog Timer desligado
#pragma config MCLRE = OFF // Master Clear desabilitado
#pragma config PBADEN = OFF // Conversor AD da porta B desligado
int cont = 1; // usado para repetir o temporizador
int periodo = 1; // periodo da onda = periodo*100
char linha1[16]; // Variável linha1 com 16 caracteres
char linha2[16]; // Variável linha2 com 16 caracteres

void setupInt(void) { // Função de configuração das interrupções
    GIE = 1; // Habilita interrupção global
    TMR0IE = 1; // interrupção do Timer 0
    INT0IE = 1; // Habilita Interrupção da INT0
    INT0IF = 0; // Zera a Flag de interrupção da INT0
    INTEDG0 = 1; // Interrupção 0 por borda crescente.
    INT2IE = 1; // Habilita Interrupção da INT0
    INT2IF = 0; // Zera a Flag de interrupção da INT0
    INTEDG2 = 1; // Interrupção 2 por borda crescente.
}

void setupTmr0() {
    T08BIT = 0; // Modo 16 bits
    T0CS = 0; // Fonte do clock (operando como temporizador, e não como contador)
    PSA = 1; // Desabilita Prescaler
    TMR0H = 0x3C; // Começa a contar de 15535
    TMR0L = 0xAF; // até 65535 (conta 50 mil vezes)
    TMR0ON = 1; // Liga o timer

}

void interrupt interrupcao(void) { // Função de atendimento da interrupção
    if (INT0IF) { // Caso a flag da INT0 esteja habilitada
        if (periodo < 9) { // verifica se o periodo é menor que 900 para poder aumentar
            cont = 1;
            periodo += 1;

        }
        INT0IF = 0; // Limpa a Flag que aciona a INT0
    }

    if (INT2IF) { // Caso a flag da INT0 esteja habilitada
        if (periodo > 1) {// verifica se o periodo é maior que 100 para poder reduzir
            cont = 1;
            periodo -= 1;

        }
        INT2IF = 0; // Limpa a Flag que aciona a INT2
    }

    if (TMR0IF) {
        if (cont == periodo) { // se o contador já repetiu a quantidade de vezes necessária para o periodo
            LATDbits.LD0 = !LATDbits.LD0;
            cont = 1;
        } else {
            cont++;
        }
        TMR0H = 0x3C; // Começa a contar de 15535
        TMR0L = 0xAF; // até 65535 (conta 50 mil vezes)
        TMR0IF = 0; // Flag do timer 0 em 0
    }
}

void main(void) { // Função principal
    TRISD = 0x00; // Porta D com todos pinos de saída
    TRISB = 0x05; // Somente pino B0 e B2 como entrada: INT0 e INT2

    Lcd_Init(); // Inicia o LCD
    sprintf(linha1, "Onda Quadrada"); // Grava texto em linha1
    Lcd_Set_Cursor(1, 1); // Posiciona o cursor na linha 1, posição 1
    Lcd_Write_String(linha1); // Escreve texto de linha1 no LCD

    setupInt(); // Chama função de configuração da Interrupção
    setupTmr0(); // Função de configurar timer 0


    while (1) { // Loop infinito
        sprintf(linha2, "Periodo: %i ms", (periodo * 100)); // Grava texto em linha1
        Lcd_Set_Cursor(2, 1); // Posiciona o cursor na linha 1, posição 1
        Lcd_Write_String(linha2); // Escreve texto de linha1 no LCD
    }
}

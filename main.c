#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"

#define BTN_HOUR_PIN   PB0
#define BTN_MINUTE_PIN PB1

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;

// Funciones para leer los botones
uint8_t isHourButtonPressed() {
    return bit_is_clear(PINB, BTN_HOUR_PIN);
}

uint8_t isMinuteButtonPressed() {
    return bit_is_clear(PINB, BTN_MINUTE_PIN);
}

// Funciones para ajustar la hora
void incrementHour() {
    hour = (hour + 1) % 24;
}

void incrementMinute() {
    minute = (minute + 1) % 60;
}

// Función para mostrar la hora en el LCD
void displayTime() {
    lcd_gotoxy(0, 0);
    fprintf(lcdout, "Hora: %02d:%02d:%02d", hour, minute, second);
}

int main() {
    DDRB = 0x00;
    PORTB = 0xFF;

    lcd_init(LCD_DISP_ON_CURSOR);

    while (1) {
        if (isHourButtonPressed()) {
            _delay_ms(100);
            incrementHour();
            displayTime();
            while (isHourButtonPressed()) {}
        }

        if (isMinuteButtonPressed()) {
            _delay_ms(100);
            incrementMinute();
            displayTime();
            while (isMinuteButtonPressed()) {}
        }
    }

    return 0;
}

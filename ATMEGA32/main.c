#include <avr/io.h>
#include <avr/interrupt.h>

#define segmentyDDR DDRB
#define segmenty PORTB
#define cyfryDDR DDRC
#define cyfry PORTC
#define grzalkaDDR DDRD
#define grzalka PORTD
#define GRZALKA_PIN 2

#define przyciskiDDR DDRD
#define przyciski PORTD
#define przyciskiPIN PIND
#define temp_g 2
#define temp_d 3
#define inkrementacja 1
#define dekrementacja 2

#define diodyDDR DDRA
#define diody PORTA
#define dioda 5

volatile uint8_t klawisz0 = 0;
volatile uint8_t klawisz1 = 0;
volatile uint8_t aktualna;
volatile uint8_t zadana;

uint8_t seg7[] = {
	~0x3F, // 0
	~0x06, // 1
	~0x5B, // 2
	~0x4F, // 3
	~0x66, // 4
	~0x6D, // 5
	~0x7D, // 6
	~0x07, // 7
	~0x7F, // 8
	~0x6F // 9
};

volatile uint8_t liczba[] = {1, 2, 3, 2, 2, 8};

volatile uint16_t wynik = 0;
volatile uint8_t pokaz = 0;

ISR(TIMER0_OVF_vect) {
	static uint8_t i = 0;
	cyfry &= ~(1<<i); // wygaszenie wszystkich cyfr
	if (i++==5) i=0;
	if (i == 1 || i == 4) {
		segmenty = seg7[liczba[i]] & 0x7F;
	} else {
		segmenty = seg7[liczba[i]];
	}
	
	cyfry |= (1 << i); // aktywacja cyfry i (wsp�lna anoda)

	if (!(przyciskiPIN & (1<<temp_g))) {
		switch (klawisz0) {
			case 0:
			klawisz0 = 1;
			break;
			case 1:
			klawisz0 = 2;
			break;
		}
	} else {
		switch (klawisz0) {
			case 3:
			klawisz0 = 4;
			break;
			case 4:
			klawisz0 = 0;
			break;
		}
	}
	
	if (!(przyciskiPIN & (1<<temp_d))) {
		switch (klawisz1) {
			case 0:
			klawisz1 = 1;
			break;
			case 1:
			klawisz1 = 2;
			break;
		}
	} else {
		switch (klawisz1) {
			case 3:
			klawisz1 = 4;
			break;
			case 4:
			klawisz1 = 0;
			break;
		}
	}
}

ISR(ADC_vect) {
	wynik = ADC;
	pokaz = 1;
}

ISR(TIMER1_COMPA_vect) {
	ADCSRA |= (1<<ADSC); // start pomiaru
}

int main(void) {
	segmentyDDR = 0xfF;
	cyfryDDR |= 0x3F;
	cyfry = 0xFF;
	//przyciskiDDR &= ~(1<<temp_g); //pin przycisk0 jako wejscie
	przyciski |= (1<<temp_g) | (1<<temp_d); //rezystor polaryzujacy

	//grzalkaDDR |= (1 << GRZALKA_PIN);
	//grzalka &= ~(1 << GRZALKA_PIN); // wy��cz grza�k�

	ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<MUX0) | (1<<MUX1) | (1<<MUX2); //Vref === 2,56V i kana� 7 na PA7
	ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS2); //wlaczenie przetwornika i przerwania przetwornika

	// Timer0 init
	TCCR0 = (1 << CS01) | (1 << CS00);
	TIMSK |= (1 << TOIE0);

	TCCR1B = (1<<WGM12) | (1<<CS12); //timer
	OCR1A = 62500;
	TIMSK |= (1<<OCIE1A);
	sei();

	while (1) {

		if (pokaz == 1) {

			//wynik = wynik/4;
			wynik = (wynik*10)/4;
			//liczba[0] = wynik / 1000;
			liczba[0] = (wynik % 1000) / 100;
			liczba[1] = ((wynik % 1000)% 100) / 10;
			liczba[2] = ((wynik % 1000)% 100) % 10;
			pokaz = 0;
		}
		
		if (klawisz0 == 2) {

			if (liczba[5]++==9) {
				liczba[5]=0;
				if (liczba[4]++==9) {
					liczba[4]=0;
					liczba[3]++;
				}
			}
			klawisz0 = 3;
		} 
		
		if (klawisz1 == 2) {
			
			if (liczba[5]--==0) {
				liczba[5]=9;
				if (liczba[4]--==0) {
					liczba[4]=9;
					liczba[3]--;
				}
			}
			klawisz1 = 3;
		}
		
		aktualna = liczba[0] * 100 + liczba[1] * 10 + liczba[2];
		zadana = liczba[3] * 100 + liczba[4] * 10 + liczba[5];
		
		if (zadana > aktualna) {
			// swieci
		} else {
			// nie swieci
		}
	}
}
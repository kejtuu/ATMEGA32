# Regulator temperatury na AVR

## Treść zadania
Napisać program, który będzie realizował regulator temperatury z wykorzystaniem  
6-pozycyjnego wyświetlacza LED oraz analogowego czujnika temperatury LM35.  

### Założenia:
- Aktualna temperatura ma być wyświetlona na wyświetlaczach 1–3, np. `24.3`
- Zadana temperatura (0,1–99,9) ma być wyświetlona na wyświetlaczach 4–6, np. `30.9`
- Układ wyposażony w dwa przyciski: **temp_g** i **temp_d**
- Krótkotrwałe naciśnięcie **temp_g** zwiększa temperaturę zadaną o `+0.1`
- Krótkotrwałe naciśnięcie **temp_d** zmniejsza temperaturę zadaną o `-0.1`
- Dioda LED świeci gdy `Tzad > Takt`, gaśnie gdy `Tzad ≤ Takt`

### Zalecenia:
- Pomiar temperatury co 1 s  
- Timer0 → odświeżanie wyświetlacza LED  
- Timer1 → odmierzanie 1 s  
- Stan regulatora na wyświetlaczu LED  
- Realizacja krokowa: najpierw wyświetlacz, potem ADC, na końcu obsługa przycisków  

---

## Opis projektu
Program napisany w C na mikrokontroler AVR (ATmega16/32).  
Czujnik LM35 podłączony do przetwornika ADC (kanał 7, PA7). Wynik konwersji jest przeliczany na temperaturę i prezentowany na pierwszych trzech cyfrach wyświetlacza 7-segmentowego. Kolejne trzy cyfry pokazują temperaturę zadaną, którą można zmieniać przyciskami.  

Timer0 służy do multipleksowania wyświetlacza i obsługi klawiatury, a Timer1 co sekundę uruchamia pomiar ADC. Na podstawie porównania `Tzad` i `Takt` zapalana jest dioda LED (i/lub sterowana grzałka).  

Projekt spełnia wszystkie wymagania zadania i może być łatwo rozszerzony np. o sterowanie przekaźnikiem dla grzałki.  

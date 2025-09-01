# 🌡️💻 Regulator temperatury na AVR
<br>

## Treść zadania
Napisać program, który będzie realizował regulator temperatury z wykorzystaniem  
6-pozycyjnego wyświetlacza LED oraz analogowego czujnika temperatury **LM35**.  

### Założenia:
- Aktualna temperatura ma być wyświetlona na wyświetlaczach o numerach od **1 do 3**, np. `24.3`
- Zadana temperatura (**0,1 – 99,9**) ma być wyświetlona na wyświetlaczach o numerach od **4 do 6**, np. `30.9`
- Układ wyposażony w dwa przyciski: **temp_g**, **temp_d**
- Naciśnięcie **temp_g** → zwiększenie temperatury zadanej o `+0.1`
- Naciśnięcie **temp_d** → zmniejszenie temperatury zadanej o `-0.1`
- Dioda LED zapala się, gdy `Tzad > Takt`, gaśnie, gdy `Tzad ≤ Takt`

### Zalecenia:
- Pomiar temperatury co **1 s**  
- **Timer0** – odświeżanie wyświetlacza LED  
- **Timer1** – odmierzanie czasu 1 s  
- Stan regulatora widoczny na 6-pozycyjnym wyświetlaczu LED  
- Program realizować krokowo: wyświetlacz → ADC → przyciski  
<br>

## Opis projektu
Program w języku **C** dla mikrokontrolera **ATmega16/32**.  
Czujnik LM35 podłączony do przetwornika ADC (kanał 7, PA7, Vref = 2.56 V).  
Wynik pomiaru prezentowany jest na **pierwszych 3 cyfrach wyświetlacza**.  
Na kolejnych **3 cyfrach** pokazywana jest temperatura zadana, ustawiana przyciskami.  

- **Timer0** → multipleksowanie wyświetlacza i obsługa przycisków  
- **Timer1** → co 1 s uruchamia pomiar ADC  
- **LED/grzałka** → świeci, gdy `Tzad > Takt`, gaśnie, gdy `Tzad ≤ Takt`  

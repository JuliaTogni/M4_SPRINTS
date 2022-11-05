// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

#define led_vermelho 42
#define led_amarelo 36
#define led_azul 45
#define led_verde 39
#define buzzer 13
#define ldr 14
#define botao 46
#define botaoFioBranco 16

// LiquidCrystal_I2C lcd(0x27, 16, 2);

int frequencia[100];
int x = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //Definindo pinos digitais dos leds e buzzer como de saída.
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_azul, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, OUTPUT);
  pinMode(botao,  INPUT_PULLUP);
  pinMode(botaoFioBranco,  INPUT_PULLUP);
}

// void display() {
//   //ligando o display
//   lcd.init();
//   lcd.backlight();
// }

int contador = 0;

void numeroBinario(int valor, int *vetor) {
  for (int i = 0; i < 4; i ++) {
    /*
      Realiza-se a divisão sucessiva por 2 (base do sistema binário).
      O resultado da conversão será dado pelo último quociente (MSB) e o agrupamento dos restos de divisão será o número binário.
      A leitura do resultado é feita do último quociente para o primeiro resto.
    */
    vetor[i] = valor % 2;
    valor = valor / 2;
  }
}

void lerValor(int *vetor) {
  int leds[4] = {42, 39, 36, 45};

  for (int i = 0; i < 4; i++) {
    if (vetor[i] == 0) {
      digitalWrite(leds[i], LOW);
    } else {
      digitalWrite(leds[i], HIGH);
    }
  }
}

void armazenaFreq(int freq) {
  frequencia[x] = freq;
  x += 1;
  tone(buzzer, freq * 100, 250);
}

void frequenciaSalva() {
  while (x >= 0) {
    tone(buzzer, frequencia[x] * 100, 250);
    // lcd.print(frequencia[x]);
    x = x - 1;
  }
}

void tocarLuz(int *vetor){
  for(int i = 0; i < 4; i++){
    numeroBinario(frequencia[i], vetor);
    lerValor(vetor);
    tone(buzzer, frequencia[i] * 100, 250);
    delay(600);
  }
}

void loop() {

  // display();
  int vetor[4] = {0, 0, 0, 0};
  int leitura = analogRead(ldr);
  // Serial.println("Leitura do Sensor de LDR:");
  // Serial.println(leitura);
  int valorLDR = leitura / 273;
  // Serial.println("Leitura LDR:");
  // Serial.println(valorLDR);

  numeroBinario(valorLDR, vetor);

  lerValor(vetor);

  if (digitalRead(botao) == LOW) {
    armazenaFreq(valorLDR);
    // lcd.print(valorLDR);
    delay(10);
    while (digitalRead(botao) == LOW) {}
  }

  if (digitalRead(botaoFioBranco) == LOW) {
    tocarLuz(vetor);
    // frequenciaSalva();
    delay(10);
    while (digitalRead(botaoFioBranco) == LOW) {}
  }

}

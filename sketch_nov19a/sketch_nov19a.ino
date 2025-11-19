/*
  Projeto: Mini-Estação Meteorológica (Datalogger)
  Autor: Joel Cassa Neto
  Curso: Licenciatura em Física - UFES
  Data: 19 de Novembro/2025
*/

//BLOCO A : Bibliotecas e Definições (Ferramentas)

// 1. INCLUSÃO DE BIBLIOTECAS
#include "DHT.h"      // Biblioteca para o sensor de temperatura/umidade
#include <SPI.h>      // Comunicação para o cartão SD
#include <SD.h>       // Biblioteca para gerenciar arquivos no SD

// 2. DEFINIÇÃO DE PINOS (HARDWARE)
// Pino onde o sensor DHT22 está conectado (Dados)
#define DHTPIN 2      
// Tipo do sensor (DHT22 é mais preciso que o DHT11)
#define DHTTYPE DHT22 

// Pino do Chip Select (CS) do Módulo SD (Geralmente pino 4 ou 10 no Uno)
const int chipSelect = 4; 

// [FUTURO] Pino do Sensor de Chuva (Analógico A0)
// #define PINO_CHUVA A0

// Inicializa o objeto do sensor DHT
DHT dht(DHTPIN, DHTTYPE);

//BLOCO B [void setup()]: Preparação
void setup() {
  // Inicia comunicação com o PC (Monitor Serial)
  Serial.begin(9600);
  while (!Serial) {
    ; // Aguarda a porta serial conectar (necessário em alguns Arduinos)
  }

  Serial.println("--- INICIANDO ESTACAO METEOROLOGICA ---");

  // Inicia o Sensor DHT
  Serial.println("Iniciando Sensor DHT22...");
  dht.begin();

  // Inicia o Cartão SD
  Serial.print("Iniciando Cartao SD...");
  // Verifica se o cartão está presente e formatado
  if (!SD.begin(chipSelect)) {
    Serial.println("FALHA NO CARTAO SD! (Verifique conexoes ou formatacao)");
    // Se falhar, o programa para aqui e não faz mais nada (loop infinito)
    while (1);
  }
  Serial.println("Cartao SD OK.");
  
  // Cria o cabeçalho no arquivo CSV (se o arquivo não existir)
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    // Escreve: Tempo(ms), Umidade(%), Temperatura(C)
    // Se o arquivo já existir, ele apenas adiciona dados novos no fim
    if (dataFile.size() == 0) {
      dataFile.println("Tempo_ms,Umidade_%,Temp_C,Chuva_Valor");
    }
    dataFile.close();
  }
}

//BLOCO C [void loop()]: Rotina 

void loop() {
  // Aguarda 2 segundos entre leituras (o DHT22 é lento)
  delay(2000);

  // --- 1. LEITURA DOS SENSORES ---
  // Tempo desde que o Arduino ligou (em milissegundos)
  unsigned long tempoAtual = millis();

  // Lê umidade (0-100%)
  float h = dht.readHumidity();
  // Lê temperatura em Celsius
  float t = dht.readTemperature();
  
  // [FUTURO] Leitura do Sensor de Chuva (0 a 1023)
  // int leituraChuva = analogRead(PINO_CHUVA);
  int leituraChuva = 0; // Placeholder enquanto não temos o sensor

  // Verifica se houve falha na leitura do DHT (retorna NaN = Not a Number)
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha ao ler do sensor DHT!"));
    return; // Tenta novamente no próximo loop
  }

  // --- 2. EXIBIÇÃO NO MONITOR SERIAL (DEBUG) ---
  Serial.print("Tempo: ");
  Serial.print(tempoAtual);
  Serial.print("ms | Umidade: ");
  Serial.print(h);
  Serial.print("% | Temp: ");
  Serial.print(t);
  Serial.print("C");
  Serial.println();

  // --- 3. GRAVAÇÃO NO CARTÃO SD ---
  // Abre o arquivo. Nota: só um arquivo pode estar aberto por vez.
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // Se o arquivo abriu, escreve os dados
  if (dataFile) {
    dataFile.print(tempoAtual);
    dataFile.print(","); // Vírgula é o separador do CSV
    dataFile.print(h);
    dataFile.print(",");
    dataFile.print(t);
    dataFile.print(",");
    dataFile.println(leituraChuva); // println para pular linha no final
    dataFile.close(); // MUITO IMPORTANTE: Salva os dados fisicamente
    // Serial.println("Dados gravados no SD.");
  }
  else {
    Serial.println("Erro ao abrir datalog.csv");
  }
}
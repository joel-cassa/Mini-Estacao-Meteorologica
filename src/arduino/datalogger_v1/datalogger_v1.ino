/*
  PROJETO: Mini-Estação Meteorológica Didática (Datalogger)
  AUTOR: Joel Cassa Neto
  CURSO: Licenciatura em Física - UFES (Alegre)
  DATA: Novembro/2025
  
  DESCRIÇÃO:
  Este firmware realiza a leitura de temperatura e umidade (DHT22) e grava
  os dados em um cartão SD (formato CSV). O sistema opera offline.
*/

// ============================================================================
// --- 1. INCLUSÃO DE BIBLIOTECAS (DEPENDÊNCIAS) ---
// ============================================================================
#include "DHT.h"      // Biblioteca oficial da Adafruit para sensores DHT
#include <SPI.h>      // Protocolo de comunicação para o módulo SD
#include <SD.h>       // Gerenciamento de arquivos no cartão SD

// ============================================================================
// --- 2. DEFINIÇÕES DE HARDWARE E CONSTANTES ---
// ============================================================================
// Configuração do Sensor DHT
#define DHTPIN 2        // Pino digital conectado ao DATA do sensor
#define DHTTYPE DHT22   // Define o modelo (DHT22 é mais preciso que DHT11)

// Configuração do Cartão SD
const int chipSelect = 4; // Pino CS (Chip Select) - Padrão Ethernet Shield/Módulos

// Nome do arquivo de dados (Máx 8.3 caracteres, ex: "dados.csv")
const char* NOME_ARQUIVO = "clima.csv";

// Intervalo entre leituras (em milissegundos)
const long INTERVALO_LEITURA = 2000; 

// ============================================================================
// --- 3. OBJETOS GLOBAIS ---
// ============================================================================
DHT dht(DHTPIN, DHTTYPE); // Instância do sensor

// ============================================================================
// --- 4. SETUP (CONFIGURAÇÃO INICIAL) ---
// Executado uma única vez ao ligar o Arduino.
// ============================================================================
void setup() {
  // A. Inicia comunicação Serial (para debug no computador)
  Serial.begin(9600);
  while (!Serial) {
    ; // Aguarda a porta serial conectar (necessário em alguns modelos)
  }

  Serial.println(F("--- INICIANDO ESTACAO METEOROLOGICA (UFES) ---"));

  // B. Inicializa o Sensor DHT
  Serial.print(F("Iniciando DHT22... "));
  dht.begin();
  Serial.println(F("OK."));

  // C. Inicializa o Cartão SD
  Serial.print(F("Iniciando Cartao SD... "));
  
  // Verifica se o cartão está inserido e formatado
  if (!SD.begin(chipSelect)) {
    Serial.println(F("FALHA! Verifique:"));
    Serial.println(F("1. O cartao esta inserido?"));
    Serial.println(F("2. A formatacao esta correta (FAT16/FAT32)?"));
    Serial.println(F("3. O pino CS esta correto?"));
    // Loop infinito de erro (pisca o LED interno para avisar, se desejar)
    while (1);
  }
  Serial.println(F("Cartao SD OK."));

  // D. Prepara o Arquivo CSV (Cabeçalho)
  // Abre o arquivo em modo de escrita (cria se não existir)
  File dataFile = SD.open(NOME_ARQUIVO, FILE_WRITE);
  
  if (dataFile) {
    // Se o arquivo estiver vazio (novo), escreve o cabeçalho
    if (dataFile.size() == 0) {
      dataFile.println("Tempo_ms,Umidade_%,Temp_C,Chuva_Valor");
      Serial.println(F("Arquivo criado com cabecalho."));
    }
    dataFile.close(); // Sempre fechar o arquivo após o uso!
  } else {
    Serial.println(F("ERRO CRITICO: Nao foi possivel abrir o arquivo no SD."));
  }
  
  Serial.println(F("--- SISTEMA PRONTO PARA COLETA ---"));
}

// ============================================================================
// --- 5. LOOP (ROTINA DE TRABALHO) ---
// Executado repetidamente enquanto houver energia.
// ============================================================================
void loop() {
  // 1. Aguarda o intervalo definido (2 segundos)
  // O DHT22 é um sensor lento, ler muito rápido retorna dados velhos ou erro.
  delay(INTERVALO_LEITURA);

  // 2. Leitura dos Sensores
  // millis() retorna o tempo em ms desde que o Arduino ligou
  unsigned long tempoAtual = millis();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // Placeholder para o sensor de chuva futuro (lê 0 por enquanto)
  int leituraChuva = 0; 

  // 3. Validação da Leitura (Segurança)
  // isnan = "Is Not a Number". Verifica se o sensor retornou erro.
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha ao ler do sensor DHT!"));
    return; // Pula o resto do loop e tenta novamente
  }

  // 4. Exibição no Monitor Serial (Para o operador ver)
  Serial.print(F("T: "));
  Serial.print(tempoAtual);
  Serial.print(F("ms | U: "));
  Serial.print(h);
  Serial.print(F("% | T: "));
  Serial.print(t);
  Serial.println(F("C"));

  // 5. Gravação no Cartão SD (Datalogging)
  File dataFile = SD.open(NOME_ARQUIVO, FILE_WRITE);
  
  if (dataFile) {
    dataFile.print(tempoAtual);
    dataFile.print(","); // CSV usa vírgula para separar colunas
    dataFile.print(h);
    dataFile.print(",");
    dataFile.print(t);
    dataFile.print(",");
    dataFile.println(leituraChuva); // println para pular linha ao final
    
    dataFile.close(); // Salva os dados fisicamente no cartão
  } else {
    Serial.println(F("Erro ao gravar dados no SD."));
  }
}

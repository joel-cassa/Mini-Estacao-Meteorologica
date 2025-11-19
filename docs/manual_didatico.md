# Manual Didático: Mini-Estação Meteorológica com Arduino

## 1. Introdução e Fundamentação Física
A coleta de dados ambientais é fundamental para compreender microclimas locais. Neste projeto, utilizamos a eletrônica embarcada para medir variáveis termodinâmicas.

### Variáveis de Estudo
* **Temperatura ($T$):** Grandeza física escalar relacionada à energia cinética média das partículas de um sistema. No sensor DHT22, utiliza-se um termistor (resistor sensível à temperatura - NTC) que varia sua resistência elétrica conforme a agitação térmica.
* **Umidade Relativa ($UR$):** Relação entre a pressão parcial de vapor de água presente no ar e a pressão de vapor de saturação à mesma temperatura. O DHT22 mede isso através da alteração na capacitância de um polímero higroscópico.

### O Microcontrolador
O **Arduino Uno** atua como o cérebro da estação. Ele realiza a **transdução**, convertendo os sinais elétricos (tensão/resistência) enviados pelos sensores em valores numéricos digitais (bits) que podemos ler e analisar.

## 2. Materiais e Diagrama de Ligação
Para reproduzir este experimento, utilizamos:
* **Arduino Uno R3**: Processamento e controle (Microcontrolador ATmega328P).
* **Sensor DHT22**: Faixa de medição de -40 a 80°C (precisão ±0.5°C) e 0-100% UR.
* **Módulo Cartão SD**: Comunicação via protocolo SPI para persistência de dados (Datalogger).
* **Fonte de Energia**: Baterias Li-Ion 18650 (3.7V) para portabilidade.

### Pinagem (Conexões)
| Componente | Pino Componente | Pino Arduino | Função |
| :--- | :--- | :--- | :--- |
| **DHT22** | VCC | 5V | Energia |
| | GND | GND | Terra |
| | DATA | D2 | Dados |
| **SD Card**| CS | D4 | Seleção do Chip (Chip Select) |
| | MOSI | D11 | Master Out Slave In (SPI) |
| | MISO | D12 | Master In Slave Out (SPI) |
| | SCK | D13 | Clock (SPI) |
| | VCC | 5V | Energia |
| | GND | GND | Terra |

## 3. Metodologia de Coleta
O sistema opera em loop contínuo com intervalo de amostragem de 2 segundos (limitação física do sensor DHT22). Os dados são gravados em um arquivo `datalog.csv` contendo o tempo de execução (`millis`) e as leituras.

# Mini-Estação Meteorológica Didática com Arduino (Datalogger)

> **Status:** Em Desenvolvimento 🚧  
> **Curso:** Licenciatura em Física - UFES (Alegre)  
> **Disciplina:** Instrumentação para o Ensino de Física / Projetos  
> **Período:** 8º Período (2025)

## 1. Resumo do Projeto
Este projeto consiste no desenvolvimento de uma estação meteorológica portátil e de baixo custo utilizando a plataforma **Arduino**. O objetivo principal é a coleta de dados físicos (Temperatura e Umidade, com expansão futura para Precipitação) para aplicação em aulas de Física (Termodinâmica e Hidrostática) e instrumentação científica.

O sistema opera no modo **Datalogger** (armazenamento offline), gravando dados em um Cartão SD para posterior análise computacional utilizando **Python (Jupyter Notebooks)**, alinhando o ensino de física com técnicas de *Scientific Machine Learning* (SciML).

## 2. Objetivos
* **Geral:** Construir um instrumento de medida autônomo para monitoramento ambiental.
* **Específicos:**
    * Aplicar conceitos de eletrônica e programação (C++ e Python).
    * Criar um manual didático para reprodução do experimento em escolas.
    * Analisar a variação térmica e higrométrica local.
    * Implementar futuramente um pluviômetro (sensor de chuva).

## 3. Hardware e Materiais
O projeto utiliza materiais acessíveis e reaproveitáveis (baseado no conceito de *Low Cost* e Cultura Maker):

* **Microcontrolador:** Arduino Uno R3.
* **Sensores:**
    * DHT22 (Temperatura e Umidade) - *Superior ao DHT11 em precisão*.
    * [Planejado] Sensor de Chuva (YL-83 ou Basculante).
* **Armazenamento:** Módulo Cartão SD.
* **Alimentação:** Baterias 18650 (3.7V) com suporte (foco em portabilidade).
* **Estrutura:** Base de acrílico e Protoboard.

## 4. Metodologia e Software
A metodologia segue o fluxo de **Transdução -> Aquisição -> Processamento -> Análise**:

1.  **Firmware (C++):** Código no Arduino para leitura dos sensores e gravação no SD (formato `.csv`).
    * *Nota:* Devido à ausência inicial de um módulo RTC (Relógio), utiliza-se o tempo relativo (`millis()`) com marco temporal definido no pós-processamento.
2.  **Análise (Python):** Uso de bibliotecas `Pandas` e `Matplotlib` no Jupyter Lab para tratamento de dados e plotagem de gráficos.

## 5. Estrutura do Repositório
* `/src`: Códigos fonte do Arduino e scripts Python.
* `/docs`: Manuais, esquemas elétricos e referências teóricas.
* `/data`: Dados brutos coletados (raw) e processados.
* `/notebooks`: Relatórios de análise de dados (Jupyter).

## 6. Referências
O projeto baseia-se em trabalhos acadêmicos correlatos, incluindo:
* ARAÚJO, R. G. *Mini-estação meteorológica utilizando Arduino*. IFG, 2018.
* SILVA, J. G. *Desenvolvimento de uma Estação Meteorológica com Arduino, Java e React*. UFU, 2024.
* Material Didático "Robótica Paraná" - Aula 34.

---
*Desenvolvido por Joel Cassa Neto.*

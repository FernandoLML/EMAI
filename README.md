# 🌿 EMAI - Estação de Monitoramento Ambiental Inteligente

![Status do Projeto](https://img.shields.io/badge/Status-Concluído-green) ![IoT](https://img.shields.io/badge/IoT-ESP32-blue) ![Firebase](https://img.shields.io/badge/Backend-Firebase-orange)

O **EMAI** é uma solução de IoT desenvolvida para monitorar a qualidade do ar e condições ambientais em tempo real. O sistema coleta dados via sensores, processa as informações usando a biblioteca BSEC (Bosch) e disponibiliza os resultados em um Dashboard Web responsivo e acessível globalmente.

<p align="center">
  <img width="1215" height="754" alt="image" src="https://github.com/user-attachments/assets/71d17e78-051d-4038-a1a9-c1abfab9dbbb" />
</p>

## 🎯 Funcionalidades

- **Monitoramento em Tempo Real:** Atualização a cada 10 segundos.
- **Métricas Coletadas:**
  - 🌡️ Temperatura (°C) com indicação de conforto térmico.
  - 💧 Umidade Relativa (%).
  - 💨 Pressão Atmosférica (hPa) e estimativa de Altitude.
  - 🍃 Qualidade do Ar (IAQ) com classificação (Bom, Moderado, Ruim).
  - 🏭 CO₂ Estimado (ppm).
- **Interface Web:** Dashboard responsivo (Mobile/Desktop) com modo escuro.
- **Diagnóstico Inteligente:** Recomendações automáticas (ex: "Ventilar o ambiente") baseadas nos dados.
- **Watchdog de Conexão:** Alerta visual se o dispositivo ficar offline.

## 🛠️ Hardware Utilizado

| Componente | Função |
|Data | Descrição |
|--- | --- |
| **ESP32** | Microcontrolador principal com Wi-Fi. |
| **BME680** | Sensor ambiental 4-em-1 (Temp, Umid, Pressão, Gás). |
| **Protoboard & Jumpers** | Conexões do protótipo. |
| **Fonte 5V / Bateria Li-Ion** | Alimentação do sistema. |

## 💻 Tecnologias

- **Firmware:** C++ (Arduino IDE), Biblioteca BSEC (Bosch), Firebase ESP Client.
- **Backend:** Google Firebase Realtime Database.
- **Frontend:** HTML5, CSS3 (Grid Layout), Javascript (ES6 Modules).
- **Hospedagem:** Firebase Hosting.

## 🚀 Como Executar o Projeto

### 1. Firmware (ESP32)
1. Instale a IDE do Arduino e configure para placas ESP32.
2. Instale as bibliotecas necessárias: `BSEC Software Library`, `Firebase ESP Client`.
3. Configure suas credenciais de Wi-Fi e Firebase no arquivo `.ino`.
4. Realize o upload para a placa.

### 2. Dashboard (Web)
1. Certifique-se de ter o Node.js instalado.
2. Instale o Firebase Tools: `npm install -g firebase-tools`.
3. Faça login: `firebase login`.
4. Na pasta `web`, execute `firebase deploy` para subir o site.

## 👥 Autores

Projeto desenvolvido pela equipe:
- **Fernando Lucas Moraes da Luz** - *Desenvolvimento de Firmware e Hardware*
- **Bruno Franzosi** - *Desenvolvimento Frontend e Integração Cloud*

## 📄 Licença

Este projeto está sob a licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

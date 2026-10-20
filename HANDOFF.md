# Continuidade do projeto DeskWisp

## Objetivo

Criar um pequeno companion de mesa com ESP32, display, entrada por encoder,
sensores ambientais, LED RGB e alertas táteis.

## Hardware confirmado

- Placa: ESP-WROOM-32, perfil PlatformIO `esp32dev`.
- Display: OLED SSD1306 I2C, 0,96 polegada, 128x64.
- Porta usada no Mac de origem: `/dev/cu.usbserial-0001`.

A porta serial pode ter outro nome em outro computador. Se necessário, remova
ou altere `upload_port` e `monitor_port` em `platformio.ini`.

## Montagem atual, já testada

```text
OLED GND ─── ESP32 GND
OLED VCC ─── ESP32 3V3
OLED SCL ─── ESP32 GPIO 22
OLED SDA ─── ESP32 GPIO 21
```

O firmware atual procura o display em `0x3C` e `0x3D`. O teste foi gravado com
sucesso e o OLED exibiu `DeskWisp` e `ESP32 OK`.

## Decisões para os próximos módulos

### Encoder rotativo

O módulo disponível possui `GND`, `5V`, `KEY`, `S1` e `S2`. A proposta inicial
é alimentá-lo com `3V3`, não 5 V, para manter sinais seguros para o ESP32:

| Encoder | ESP32 proposto |
|---|---|
| `GND` | `GND` |
| `5V` (alimentação do módulo) | `3V3` |
| `KEY` | `GPIO 25` |
| `S1` | `GPIO 32` |
| `S2` | `GPIO 33` |

Essas conexões ainda não foram montadas nem testadas.

### Sensor de temperatura

O módulo possui `VDD`, `SDA`, `GND` e `SCL`. Ele poderá compartilhar o
barramento I2C do OLED:

- `VDD` em `3V3`;
- `GND` em `GND`;
- `SDA` em `GPIO 21`;
- `SCL` em `GPIO 22`.

O modelo/endereço do sensor ainda precisa ser identificado antes do firmware.

### LED RGB

Há um LED RGB de quatro terminais. Ainda é preciso identificar se ele é ânodo
comum ou cátodo comum e mapear as três cores. Cada cor deverá ter seu próprio
resistor, tipicamente de 220 a 330 ohms.

### Motor de vibração

O motor veio de um joystick de PlayStation 2. A preferência é usar somente a
alimentação USB, mas o motor não pode ser conectado diretamente a um GPIO. A
solução mínima considerada é um pequeno módulo MOSFET compatível com sinal de
3,3 V ou um driver como o DRV8833. O motor menor é preferível por consumir
menos e reduzir o risco de reiniciar o ESP32.

## Próximo passo recomendado

Conectar e testar o encoder sem alterar a montagem do OLED. O teste deve:

1. manter a mensagem no OLED;
2. mostrar um contador na tela;
3. incrementar/decrementar conforme o sentido do giro;
4. indicar o pressionamento do botão `KEY`;
5. registrar os eventos na porta serial para diagnóstico.

## Cuidados

- Desconectar o USB antes de mexer nos fios.
- Usar `3V3` para os módulos lógicos, salvo especificação confirmada em contrário.
- Todos os módulos devem compartilhar o mesmo `GND`.
- Não alimentar motor diretamente por GPIO.
- Não ligar LED sem resistor limitador de corrente.

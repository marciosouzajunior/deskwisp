# DeskWisp

DeskWisp é um desktop companion baseado em ESP32, com interface em OLED,
controles físicos, sensores e feedback visual/tátil.

## Estado atual

O primeiro protótipo está funcionando com:

- ESP-WROOM-32 / ESP32 Dev Module;
- OLED SSD1306 I2C de 0,96 polegada e resolução 128x64;
- firmware compilado e gravado pelo PlatformIO;
- detecção automática do OLED nos endereços `0x3C` e `0x3D`;
- exibição de `DeskWisp` e `ESP32 OK`.

## Conexões testadas

| OLED SSD1306 | ESP32 |
|---|---|
| `GND` | `GND` |
| `VCC` | `3V3` |
| `SCL` | `GPIO 22` |
| `SDA` | `GPIO 21` |

Faça ou altere conexões somente com o ESP32 desconectado do USB.

## Preparação do ambiente

1. Instale o PlatformIO Core ou use a extensão PlatformIO no VS Code.
2. Conecte o ESP32 por USB.
3. Confira a porta serial configurada em `platformio.ini`.
4. Compile e grave:

```bash
pio run --target upload
```

5. Para acompanhar as mensagens seriais:

```bash
pio device monitor
```

## Próximos componentes planejados

- encoder rotativo (`GND`, alimentação, `KEY`, `S1` e `S2`);
- sensor de temperatura I2C compartilhando `SDA` e `SCL` com o OLED;
- LED RGB de quatro terminais, com um resistor por cor;
- motor de vibração reaproveitado de joystick de PlayStation 2, acionado por
  driver/MOSFET e nunca diretamente por um GPIO.

Consulte [HANDOFF.md](HANDOFF.md) para o contexto técnico e a continuação do
projeto em outro computador.

# Aplicativo de Monitoramento de Saúde Mental

Este projeto visa abordar a questão da saúde mental, oferecendo suporte personalizado através de um aplicativo inovador. A solução proposta utiliza tecnologias para mostrar dicas de relaxamento

## Configuração e Execução

### Requisitos
- Placa ESP32 ou compatível
- WiFi
- Broker MQTT (utilizado broker.hivemq.com como exemplo)
- Bibliotecas:
  - WiFi.h
  - Adafruit_GFX.h
  - Adafruit_ILI9341.h
  - PubSubClient.h

### Configuração do Hardware
1. Conecte a placa ESP32 ao seu computador.
2. Certifique-se de que a placa tenha acesso à rede WiFi "Wokwi-GUEST".

### Configuração do Software
1. Abra o código fornecido em um ambiente de desenvolvimento compatível com o ESP32 (por exemplo, Arduino IDE).
2. Substitua as informações de WiFi, MQTT e outras configurações conforme necessário.
3. Carregue o código na placa ESP32.

### Execução
1. Abra a porta serial no ambiente de desenvolvimento para monitorar a saída.
2. O aplicativo se conectará à rede WiFi e ao servidor MQTT.
3. O LCD exibirá a mensagem de conexão bem-sucedida.
4. Pressione o botão físico na porta definida pelo `BTN_PIN` para enviar dicas de relaxamento para o servidor MQTT.

## Simulação do Projeto no Wokwi
Para simular o projeto, acesse o [link de simulação no Wokwi](https://wokwi.com/projects/381427231903545345https://wokwi.com/projects/381427231903545345). A simulação permite visualizar a interação do aplicativo com o LCD e a publicação de dicas de relaxamento no servidor MQTT.

**Observação:** Lembre-se de que essa simulação é um ambiente virtual e algumas funcionalidades específicas da placa ESP32 podem não ser totalmente reproduzidas.

---

Este é um guia básico para configurar e executar o projeto. Certifique-se de ler a documentação específica para as bibliotecas e a plataforma ESP32 para obter informações adicionais e suporte.

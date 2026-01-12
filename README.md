# Control-de-Carrito-con-control-gen-rica
Este programa está diseñado para placa ESP32 para un carrito por control de un xbox series (Tambien se puede hacer uso de un control generico)

El programa consiste en un robot móvil controlado mediante una placa o módulo ESP32, que envía señales al driver de motores L298N para mover un vehículo de tres motores DC (dos de impulso y uno para volante) aparte de que el sistema utiliza una alimentación externa basada en dos baterías de lion conectadas para entregar el voltaje necesario al módulo de potencia. 

Nota importante: Para poder ejecutar muy bien el programa es necesaio descargar unos paquetes y unas bibliotecas para su gran ejecucion. 

1. Primero hay que insertar estos links en Preferencias -> URLs adicionales de gestor de placas: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json

Esto hara qye pueda usarse las placas y la liberia de BluePad32

2: Hay que descargar Arduino AVR Boards de Arduino y Arduino ESP32 Board de Arduino. Esto hara que se implenten mas las placas de uso para el ESP32

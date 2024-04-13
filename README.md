<p align="center">
    <img src="img/paddy_infra.png" alt="logo" width="250"/>
</p>

> ⚠️ Documentation is still WIP. Expect more updates around May.

# Paddy Firmware

This is the firmware component for Paddy, the Power Administration Daemon.

It uses Arduino C++ and is flashed directly on a supported chip. The Arduino type used for this project is an IoT Nano 33.

The job of this code is to interface with the Paddy MQTT Broker through Wi-Fi, or the Paddy App through Bluetooth Low Energy, for setup & error handling. The code should also control the hardware that performs:

1. On/Off toggling of the load device
2. Power measurement for the load device, with periodic statistic sending.
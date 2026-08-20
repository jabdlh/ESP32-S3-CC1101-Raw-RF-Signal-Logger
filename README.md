\# ESP32-S3 CC1101 Raw RF Signal Logger



A simple script for the ESP32-S3 and a CC1101 module to capture and log raw radio frequency signals (like 433.92 MHz ASK/OOK transmissions). 



It measures the exact duration of high pulses and low gaps, saving them into a small batch so you can easily read them in the Serial monitor and spot sync gaps to decode signals.



\## What it Does

\* Captures raw high and low pulse durations in microseconds.

\* Buffers the data into an array so the Serial monitor doesn't lag or miss data.

\* Automatically flags long low gaps (`> 5000µs`) to help you find packet boundaries and sync markers.



\## Hardware Wiring

\* \*\*ESP32-S3\*\* connected to a \*\*CC1101 transceiver module\*\*.

\* \*\*GDO0 Pin:\*\* Connected to `GPIO 2` on the ESP32-S3.

\* \*\*SPI Pins:\*\* Set to `12` (MOSI), `13` (MISO), `11` (SCK), and `10` (CS).



\## Requirements

You will need this library installed in your Arduino IDE:

\* \[ELECHOUSE\_CC1101\_SRC\_DRV](https://github.com/LSatan/SmartRC-CC1101-Driver-Lib)



\## How to Use

1\. Flash the code to your ESP32-S3.

2\. Open your \*\*Serial Monitor\*\* at `115200` baud.

3\. Trigger your RF remote or device near the antenna.

4\. Look at the printed timings and watch for the `\[SYNC GAP DETECTED]` message to figure out the structure of the signal.


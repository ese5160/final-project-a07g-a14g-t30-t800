[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/OpMbFSfa)
# final-project-skeleton

This codebase will be used first in A07G Exploring the CLI, then will be expanded upon in parts of A08G Comm Protocols, A09G The Bootloader Waltz, A10G Cloud, A12G Firmware Drivers, and A14G Final Submission. Please write the answers in the README file corresponding to the assignment number - not this one!

## GitHub Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)

## 1.
### 1.
HRS 01
The system shall use a SAMW25 microcontroller with integrated Wi-Fi for real-time data transmission and remote monitoring.

HRS 02
The system shall be powered by a single Lithium Ion cylindrical cell to enable portable and sustainable operations.

HRS 03
The system shall include CO₂, temperature, and humidity sensors in each crop zone. These sensors shall communicate with the microcontroller via I2C and operate within manufacturer-specified accuracy and range limits.

HRS 04
Motors for window adjustment and electromagnetic valves for irrigation shall be incorporated. They shall be physically robust enough to operate in typical greenhouse conditions (temperature, humidity, and dust).

HRS 05
The I2C bus shall be used for sensor data collection to reduce wiring complexity and ensure efficient data transfer rates suitable for real-time control.

HRS 06
The motors and valves should be mounted on a stable overhead track to facilitate precise and targeted irrigation without disturbing neighboring crop zones.

HRS 07
The system should support USB external power supply: The system should be capable of being powered via a USB interface during code programming or when continuous operation is needed. Additionally, the system should also support standalone operation powered by a lithium-ion battery, ensuring continuous functionality when no external power source is available.

SRS 01 – Environmental Monitoring: Each sensor module shall measure the concentration of CO2, ambient temperature, and humidity within its designated zone. Measurements of CO2 and temperature shall be taken every 30 seconds +/- 5 seconds; humidity shall be measured every 60 seconds +/- 10 seconds.

SRS 02 – Actuator Control: Based on sensor inputs, the system shall control actuators to adjust environmental conditions. If CO2 levels exceed pre-defined thresholds appropriate for the crops in any zone, ventilation windows shall be opened automatically within 5 seconds of detection. If humidity drops below the set threshold, irrigation shall be activated within 10 seconds.

SRS 03 – Remote Data Access: The system shall provide real-time environmental data to users via a GUI accessible through standard web browsers. The GUI shall update sensor readings every minute.

SRS 04 – System Configuration and Alerts: Users shall be able to configure threshold values for CO2, temperature, and humidity for each zone through the GUI. The system shall send alerts to the user's registered email or mobile device when any threshold is breached.

SRS 05 – Energy Management: The system shall monitor its battery status and notify users when the battery level falls below 20%. It should also enter a low-power mode if no user interaction occurs within a 24-hour period, while maintaining minimum monitoring functionality.

SRS 06 – Log Data: The system shall log all sensor data with timestamps in a local database, accessible to the user for download and analysis. The data shall be stored for at least one year before archival.

SRS 07 – Software Updates: The device shall be capable of receiving firmware updates over-the-air via Wi-Fi, without requiring physical access to the hardware.

### 2.

<img width="921" alt="截屏2025-03-20 17 49 56" src="https://github.com/user-attachments/assets/42200a46-89d0-4b21-ac4f-74787285a055" />

### 3.
<img width="782" alt="截屏2025-03-20 18 07 36" src="https://github.com/user-attachments/assets/05e90916-866a-459b-9007-c6274aef5404" />



## 2.
To address your questions comprehensively, we'll go through the functional breakdown of the UART interface in the context of the SAMW25 starter code, typically utilizing Microchip Studio and FreeRTOS:

### 1. **Function of `InitializeSerialConsole()`**
   This function sets up the UART communication by configuring UART settings such as baud rate, parity, and stop bits. It likely initializes the UART hardware to work at 115200 baud with 8 data bits, no parity bit, and one stop bit (8N1 configuration).

### 2. **`cbufRx` and `cbufTx` Explanation**
   - **cbufRx** and **cbufTx** are likely structures used for handling circular buffers for UART communication.
   - **Type of data structure:** These are circular (or ring) buffers, which are linear data structures that follow a first-in-first-out (FIFO) method but are implemented in a circular way to efficiently use buffer space, allowing the buffer to wrap around to the beginning when it reaches the end.

### 3. **Initialization of `cbufRx` and `cbufTx`**
   These buffers are initialized in the `InitializeSerialConsole()` function. The exact initialization would typically involve setting the head and tail pointers to the start of the buffer, and defining the size of the buffer.

### 4. **Library Definition**
   The definitions for `cbufRx` and `cbufTx` likely come from a circular buffer library, often found in a file like `circular_buffer.c` or within the UART driver code itself, possibly named `uart_driver.c`.

### 5. **Storage Arrays for RX and TX Characters**
   The character arrays where the received (RX) and transmitted (TX) characters are stored are typically defined within the circular buffer structure. The names and sizes of these arrays can vary but are typically defined as part of the circular buffer structure initialization, such as `rxBuffer[SIZE]` and `txBuffer[SIZE]`, where `SIZE` is the defined buffer size.

### 6. **UART Interrupts Definition**
   The interrupts for UART character reception and transmission are defined within the UART configuration settings in the MCU setup code, possibly in `uart_driver.c`.

### 7. **Callback Functions**
   - **RX callback:** This function is triggered when a character is received via UART. It typically reads the character from the UART data register and adds it to `cbufRx`.
   - **TX callback:** This function is activated when a UART transmit operation completes. It checks if there is more data to send in `cbufTx` and, if so, initiates the transmission of the next character.

### 8. **Callback Function Operations**
   - **RX Callback:** Adds received characters to `cbufRx`, handling overflow if necessary.
   - **TX Callback:** Sends characters from `cbufTx`, managing buffer underflow conditions.

### 9. **Diagrams for Program Flow**
   For the diagrams illustrating the program flows for UART receive and transmit processes, it would involve the sequence of functions and buffer operations starting from character entry to buffer storage and from buffer retrieval to display. Diagrams can be sketched or described based on your specific starter code implementation.

### 10. **Function of `startStasks()` in `main.c`**
   This function initializes and starts FreeRTOS tasks. The exact number and nature of tasks started depend on your specific application, but typically it would start tasks for handling UART communication, possibly other sensor interfaces or logic depending on the project requirements.






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
# Understanding the Starter Code

### 1. InitializeSerialConsole() function
`InitializeSerialConsole()` initializes the UART serial communication at 115200 baud 8N1. In this function:
- `cbufRx` is a circular buffer for receiving characters from UART
- `cbufTx` is a circular buffer for transmitting characters via UART
- Both are circular buffer data structures that efficiently manage incoming and outgoing data in a ring structure

### 2. Circular buffer initialization
`cbufRx` and `cbufTx` are initialized using the `circular_buf_init()` function defined in `circular_buffer.c`. This library provides the implementation for all circular buffer operations including initialization, push, and pop.

### 3. Character storage arrays
The character arrays where RX and TX characters are stored:
- `rxCharacterBuffer` - stores received characters within the `cbufRx` structure
- `txCharacterBuffer` - stores characters to be transmitted within the `cbufTx` structure
- Both arrays have sizes defined as constants: `RX_BUFFER_SIZE` and `TX_BUFFER_SIZE`, which are both 512 bytes

### 4. UART interrupt definitions
UART interrupts are defined in SerialConsole.c's `configure_usart_callbacks()` function where callbacks are registered for UART events:
```c
usart_register_callback(&usart_instance, usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
usart_register_callback(&usart_instance, usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
```

### 5. Callback functions
- **RX callback**: `usart_read_callback()` - called when a character is received
- **TX callback**: `usart_write_callback()` - called when a character has been sent and the hardware is ready for the next character

### 6. Callback operations
- **usart_read_callback**: When a character is received, the interrupt triggers this callback. It should read the character from `latestRx` (which was filled by the UART hardware), add it to the `cbufRx` circular buffer using `circular_buf_put()`, and then start a new read operation with `usart_read_buffer_job()`. This callback is marked as incomplete in the code.

- **usart_write_callback**: When the UART has finished sending a character, this callback is triggered. It pops the next character from `cbufTx` using `circular_buf_get()` and loads it into `latestTx`, then initiates transmission of this character if the buffer is not empty. If the buffer is empty, no further transmission is started.

### 7. UART Receive Flow Diagram

```
User types character on terminal → 
UART hardware receives character → 
UART RX interrupt triggered → 
usart_read_callback() executes → 
Character read from latestRx → 
circular_buf_put(cbufRx, receivedChar) → 
Character stored in rxBuffer within cbufRx → 
Start new read with usart_read_buffer_job() →
SerialConsoleReadCharacter() can retrieve character from cbufRx
```

### 8. UART Transmit Flow Diagram

```
Program calls SerialConsoleWriteString(string) → 
Characters pushed to cbufTx using circular_buf_put() → 
First character popped from cbufTx → 
Character loaded into latestTx → 
usart_write_buffer_job() sends character → 
Character transmitted by UART hardware → 
TX complete interrupt triggered → 
usart_write_callback() executes → 
Next character popped from cbufTx → 
Process repeats until cbufTx empty → 
Characters appear on PC terminal (Teraterm)
```

### 9. startTasks() function
 the `startTasks()` function in main.c is responsible for initializing and starting FreeRTOS tasks. While we don't have the exact implementation, it appears to start at least one thread - the Command Console Task (`vCommandConsoleTask`), which handles user commands through the CLI interface. 

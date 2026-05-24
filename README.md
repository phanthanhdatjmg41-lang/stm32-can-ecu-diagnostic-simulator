# STM32 CAN ECU Diagnostic Simulator

## 1. Project Overview

This project is an **STM32F7-based ECU Diagnostic Simulator** using **UART command-line interface** and **CAN loopback communication**.

The system simulates a simple automotive ECU with:

- ECU state machine
- DTC fault simulation
- UART command control via Tera Term
- CAN TX/RX loopback frames
- CAN status monitoring
- Periodic CAN diagnostic reporting
- Diagnostic report over UART

This project was built to demonstrate embedded C programming, STM32 HAL usage, UART communication, CAN communication, and modular firmware design.

---

## 2. Main Features

### UART Command Line Interface

The user can control the ECU through Tera Term using text commands such as:

```text
help
status
start
stop
reset
sleep
set dtc P0001
set dtc P0002
set dtc P0003
clear dtc
```

### ECU State Machine

The ECU can switch between different states:

```text
INIT
IDLE
RUNNING
ERROR
SLEEP
```

### DTC Fault Simulation

The project supports simulated diagnostic trouble codes:

| DTC Code | Description  |
| -------- | ------------ |
| NONE     | No fault     |
| P0001    | SENSOR_FAIL  |
| P0002    | COMM_TIMEOUT |
| P0003    | LOW_VOLTAGE  |

### CAN Loopback Communication

The project uses CAN loopback mode to test CAN transmission and reception without requiring an external CAN transceiver or another CAN node.

Supported CAN commands:

```text
can test
can status
can dtc
can ecu
can all
can auto on
can auto off
can auto status
```

### Diagnostic Report

The command:

```text
diag report
```

prints a full diagnostic report including:

* ECU state
* Current DTC code
* DTC description
* Last log event
* INFO log count
* WARNING log count
* ERROR log count

---

## 3. Hardware Used

| Component                      | Description                          |
| ------------------------------ | ------------------------------------ |
| STM32F746 board                | Main microcontroller board           |
| USB-UART module / onboard UART | Used for Tera Term command interface |
| PC                             | Used for STM32CubeIDE and Tera Term  |

UART configuration:

```text
Baudrate    : 115200
Data bits   : 8
Parity      : None
Stop bits   : 1
Flow control: None
```

---

## 4. Software Used

| Tool             | Purpose                                     |
| ---------------- | ------------------------------------------- |
| STM32CubeIDE     | Project configuration, coding, build, debug |
| STM32 HAL Driver | Peripheral control                          |
| Tera Term        | UART terminal                               |
| GitHub           | Source code hosting                         |

---

## 5. Software Architecture

The project is divided into multiple modules:

```text
Core/Inc
├── app_uart.h
├── app_log.h
├── app_ecu.h
├── app_dtc.h
├── app_command.h
├── app_heartbeat.h
└── app_can.h

Core/Src
├── app_uart.c
├── app_log.c
├── app_ecu.c
├── app_dtc.c
├── app_command.c
├── app_heartbeat.c
└── app_can.c
```

### Module Description

| Module          | Description                                                   |
| --------------- | ------------------------------------------------------------- |
| `app_uart`      | Handles UART transmit and receive command processing          |
| `app_log`       | Stores and prints system logs                                 |
| `app_ecu`       | Manages ECU state machine                                     |
| `app_dtc`       | Manages diagnostic trouble codes                              |
| `app_command`   | Parses and executes UART commands                             |
| `app_heartbeat` | Periodically prints ECU status                                |
| `app_can`       | Handles CAN initialization, TX/RX, status, and auto reporting |

---

## 6. UART Command List

| Command           | Description                     |
| ----------------- | ------------------------------- |
| `help`            | Show command list               |
| `status`          | Show ECU status                 |
| `start`           | Start ECU                       |
| `stop`            | Stop ECU                        |
| `reset`           | Reset ECU and clear DTC         |
| `sleep`           | Put ECU into sleep state        |
| `set dtc P0001`   | Set SENSOR_FAIL fault           |
| `set dtc P0002`   | Set COMM_TIMEOUT fault          |
| `set dtc P0003`   | Set LOW_VOLTAGE fault           |
| `clear dtc`       | Clear current DTC               |
| `can test`        | Send CAN test frame             |
| `can status`      | Show CAN status                 |
| `can dtc`         | Send current DTC over CAN       |
| `can ecu`         | Send current ECU state over CAN |
| `can all`         | Send ECU state and DTC over CAN |
| `can auto on`     | Enable periodic CAN report      |
| `can auto off`    | Disable periodic CAN report     |
| `can auto status` | Show CAN auto report status     |
| `diag report`     | Show full diagnostic report     |

---

## 7. CAN Frame Format

### CAN Test Frame

| Field   | Value   |
| ------- | ------- |
| CAN ID  | `0x100` |
| DLC     | `1`     |
| Data[0] | `0x01`  |

Example output:

```text
[INFO] CAN TX ID=0x100 DATA=01
[INFO] CAN RX ID=0x100 DLC=1 DATA=01 00 00 00 00 00 00 00
```

---

### CAN DTC Frame

| Field   | Value            |
| ------- | ---------------- |
| CAN ID  | `0x321`          |
| DLC     | `1`              |
| Data[0] | Current DTC code |

DTC data mapping:

| Data[0] | Meaning            |
| ------- | ------------------ |
| `0x00`  | NONE               |
| `0x01`  | P0001 SENSOR_FAIL  |
| `0x02`  | P0002 COMM_TIMEOUT |
| `0x03`  | P0003 LOW_VOLTAGE  |

Example output:

```text
[INFO] CAN TX DTC ID=0x321 DTC=P0002 DATA=02
[INFO] CAN RX ID=0x321 DLC=1 DATA=02 00 00 00 00 00 00 00
```

---

### CAN ECU State Frame

| Field   | Value             |
| ------- | ----------------- |
| CAN ID  | `0x322`           |
| DLC     | `1`               |
| Data[0] | Current ECU state |

ECU state mapping:

| Data[0] | Meaning |
| ------- | ------- |
| `0x00`  | INIT    |
| `0x01`  | IDLE    |
| `0x02`  | RUNNING |
| `0x03`  | ERROR   |
| `0x04`  | SLEEP   |

Example output:

```text
[INFO] CAN TX ECU ID=0x322 ECU=RUNNING DATA=02
[INFO] CAN RX ID=0x322 DLC=1 DATA=02 00 00 00 00 00 00 00
```

---

## 8. Example Test Flow

### Basic ECU Test

```text
help
status
start
status
sleep
status
reset
status
```

### DTC Test

```text
set dtc P0001
status
diag report
clear dtc
status
```

### CAN Test

```text
can status
can test
can ecu
can dtc
can all
```

### CAN Auto Report Test

```text
can auto status
can auto on
set dtc P0002
diag report
can auto off
```

---

## 9. Demo Output

Example diagnostic report:

```text
===== DIAGNOSTIC REPORT =====
ECU State    : ERROR
DTC Code     : P0002
DTC Desc     : COMM_TIMEOUT
Last Event   : DTC P0002 COMM_TIMEOUT
Info Count   : 10
Warn Count   : 0
Error Count  : 2
=============================
```

Example CAN status:

```text
===== CAN STATUS =====
CAN State : LISTENING
CAN Error : 0x00000000
RX FIFO0  : 0
TX Free   : 3
======================
```

---

## 10. How to Build and Run

1. Open the project with **STM32CubeIDE**.
2. Open the `.ioc` file and verify:

   * USART is configured in asynchronous mode.
   * CAN is configured in loopback mode.
3. Build the project.
4. Flash the program to the STM32 board.
5. Open Tera Term.
6. Select the correct COM port.
7. Configure UART:

```text
Baudrate    : 115200
Data bits   : 8
Parity      : None
Stop bits   : 1
Flow control: None
```

8. Press reset on the board.
9. Type:

```text
help
```

---

## 11. Project Highlights

This project demonstrates:

* Embedded C programming
* Modular firmware architecture
* STM32 HAL driver usage
* UART interrupt-based command interface
* CAN loopback TX/RX communication
* ECU state machine design
* DTC fault simulation
* Periodic CAN diagnostic reporting
* Debugging through UART logs

---

## 12. Future Improvements

Possible improvements:

* Add real CAN transceiver support
* Communicate with another STM32 board through CAN bus
* Add UDS-like diagnostic commands
* Add CAN frame parser
* Add EEPROM/Flash storage for DTC history
* Add FreeRTOS tasks for UART, CAN, and ECU logic
* Add PC-based CAN dashboard

---

## 13. CV Description

**STM32 CAN ECU Diagnostic Simulator**

Developed an STM32F7-based ECU diagnostic simulator using UART command-line interface and CAN loopback communication. Implemented ECU state machine, DTC fault simulation, CAN TX/RX frames, periodic CAN reporting, and diagnostic report over UART. Used STM32CubeIDE, STM32 HAL drivers, USART, bxCAN, and modular embedded C architecture.

---

## 14. Author

**Phan Thanh Dat**

Embedded Systems / Automotive Software Project

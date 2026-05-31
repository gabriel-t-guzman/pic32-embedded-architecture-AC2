# PIC32 Embedded Systems & Architecture (AC2)

##  Overview
This repository contains a chronological log of laboratory exercises and firmware developed for the **Arquitectura de Computadores 2** course at the **Universidade de Aveiro**. 

The projects focus on low-level embedded systems programming utilizing the **PIC32 MX** microcontroller (MIPS32 architecture). The curriculum transitions from bare-metal Assembly routines to structured C firmware to interact directly with hardware registers and manage real-time peripherals.

##  Repository Structure & Learning Path
The codebase is organized week by week (*Aulas*), mapping out the hardware abstraction progress throughout the semester:

###  Phase 1: Bare-Metal Assembly (Aulas 01 - 03)
* **`/aula01` to `/aula03`**: Initial standalone programs written in pure **MIPS32 Assembly** (`.s`). Focuses on instruction set architecture (ISA), manual register allocation, bitwise masking, logic/arithmetic operations, and structural control flows (conditional jumps and loops).

###  Phase 2: Microcontroller Peripherals in C (Aulas 04 - 10)
* **`/aula04` to `/aula10`**: Advanced modular firmware written in **C** (`.c`) targeting hardware configuration registers directly to manage embedded subsystems:
    * **Digital I/O:** Interfacing with General Purpose Input/Output (GPIO) pins to control displays, switches, and LEDs.
    * **Timers & Counters:** Configuring internal hardware timers to create exact time delays, polling mechanisms, and frequency controllers.
    * **Interrupts:** Implementing high-performance Interrupt Service Routines (ISRs) to handle asynchronous hardware events without blocking the main CPU loop.
    * **Analog-to-Digital Conversion (ADC):** Sampling analog signals and transforming sensor inputs into digital data tracks.

##  Technical Concepts Demonstrated
* **Memory-Mapped I/O:** Reading and writing directly to specific hardware memory addresses using pointer casting in C.
* **Bit Manipulation:** Heavy reliance on bitwise operators (`&`, `|`, `^`, `~`) and register bit-masks (`SET`, `CLR`, `INV` registers) to toggle hardware states safely.
* **Concurrency Basics:** Managing real-time triggers using non-blocking hardware interrupts rather than software delay loops.

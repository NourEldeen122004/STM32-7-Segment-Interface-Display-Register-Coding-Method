# 🔢 STM32 7-Segment Display Interface (Register Coding Method)

This repository demonstrates how to interface a **7-segment display** with the **STM32F446RET6** microcontroller using **pure register-level programming** (no HAL, no CubeMX logic).

The project is aimed at **embedded beginners** who want to understand **what actually happens at the register level** when driving a display.

---

## 📌 Project Overview

* Controller: **STM32F446RET6 (NUCLEO Board)**
* Display: **Single-digit 7-Segment (Common Cathode)**
* Coding Style: **Direct Register Programming**
* IDE: **STM32CubeIDE**
* Logic Demonstrated:

  * Display numbers **0 → 9**
  * Reverse count **8 → 1**
  * Continuous loop operation

This project focuses on **GPIO register control** without any abstraction layers.

---

## 🧠 Why Register Coding?

HAL is powerful, but register coding helps you:

* Understand **STM32 hardware internals**
* Gain **fine-grained control** over peripherals
* Improve **debugging confidence**
* Prepare for **interviews and low-level roles**
* Write **efficient and deterministic code**

This repo intentionally avoids HAL APIs to keep learning transparent.

---

## 🔌 Hardware Connections

**7-Segment (Common Cathode) → STM32F446RET6**

| Segment | STM32 Pin |
| ------- | --------- |
| a       | D7        |
| b       | D8        |
| c       | D9        |
| d       | D10       |
| e       | D11       |
| f       | D12       |
| g       | D13       |

> ⚠️ Use **current-limiting resistors (220Ω – 330Ω)** for each segment.

---

## 🔧 Pin Configuration (Register Level)

* GPIO Port: **GPIOA / GPIOB (based on board mapping)**
* Mode: **General Purpose Output**
* Output Type: **Push-Pull**
* Speed: **Low / Medium**
* Pull-up/Pull-down: **None**

Configured manually using:

* `RCC->AHB1ENR`
* `GPIOx->MODER`
* `GPIOx->ODR`

No `.ioc` pin logic is used.

---

## 🧮 Display Logic

Each digit is represented by a bit pattern for segments **a–g**.

Example:

```c
// Digit 0 (a b c d e f ON, g OFF)
0b0111111
```

The code:

1. Clears GPIO output
2. Sets required segment bits
3. Applies delay
4. Moves to next digit

Reverse counting uses the same logic in opposite order.

---

## ⏱ Delay Implementation

* Software delay using a simple loop
* No SysTick or timer abstraction
* Helps beginners visualize execution timing

---

## 📂 Project Structure

```
STM32-7-Segment-Interface-Display-Register-Coding-Method
├── Core
│   ├── Src
│   │   └── main.c        // Complete register-level logic
│   └── Inc
├── Drivers
├── STM32CubeIDE files
└── README.md
```

Focus file: **`Core/Src/main.c`**

---

## ▶️ How to Run

1. Clone the repository:

```bash
git clone https://github.com/DanielRajChristeen/STM32-7-Segment-Interface-Display-Register-Coding-Method.git
```

2. Open using **STM32CubeIDE**
3. Build the project
4. Flash to **NUCLEO-F446RE**
5. Observe the 7-segment counting sequence

---

## 🧪 Learning Outcomes

After completing this project, you will understand:

* GPIO clock enabling using RCC
* GPIO mode configuration via registers
* Output Data Register (ODR) manipulation
* Binary mapping of display segments
* Difference between HAL vs Register coding
* Practical embedded debugging mindset

---

## 🧩 Extensions You Can Try

* Add decimal point (DP)
* Use **Common Anode** display
* Convert logic to **HAL method**
* Replace delay loop with **SysTick**
* Extend to **multi-digit multiplexing**

---

## 📜 License

This project is licensed under the **MIT License**.
Feel free to use, modify, and share for learning and teaching.

---

## 🤝 Contribution & Feedback

This repo is built for **learning-by-doing**.
Suggestions, issues, and improvements are always welcome.

If this helped you, ⭐ star the repo and keep learning embedded systems the right way.

---

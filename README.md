# 🛰️ Minitalk

**Minitalk** demonstrates inter-process communication between a **client** and a **server** using **Unix signals**.  
Instead of sockets or shared memory, this project sends data bit-by-bit using:

- **SIGUSR1** → represents binary `0`
- **SIGUSR2** → represents binary `1`

A **handshake mechanism** ensures that each bit is acknowledged before the next is sent, guaranteeing error-free transmission — even for **Unicode** characters.

---

## ✨ Features
- **Unicode support** (multi-byte message handling)
- **Error-free transmission** using handshake acknowledgment
- Runs entirely over **Unix signals**
- Lightweight and easy to understand

---

## 📚 Table of Contents
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Installation](#-installation)
- [Usage](#-usage)
- [How It Works](#-how-it-works)
- [Key Functions](#-key-functions)
- [Requirements](#-requirements)

---

## 📁 Project Structure

- `server.c` – Handles incoming signals and prints the received message.
- `client.c` – Sends the message bit by bit to the server.
- `libft/` – (If applicable) Custom implementations of common C functions.
- `Makefile` – Builds the client and server binaries.

🚀 Usage


# 🛰️ Minitalk

**Minitalk** demonstrates how two programms — a **client** and a **server** — can communicate using **Unix signals** as a data transmission medium. The client sends messages bit-by-bit using:

- **SIGUSR1** → represents binary `0`
- **SIGUSR2** → represents binary `1`

A **handshake mechanism** ensures that each bit is acknowledged before the next is sent, guaranteeing error-free transmission — even for **Unicode** characters. This handshake mechanism makes Minitalk a simple but robust example of inter-process communication.

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

## ⚙️ Installation

1. Clone the repository

```git clone https://github.com/yourusername/minitalk.git```

2. Change directories

```cd minitalk```

3. Compile both server and client

```make```

## 🚀 Usage

1. Start the server (prints its PID)
`./server`

2. Send a message from the client (use the server PID)
`./client <server_pid> "Your message here"`

Example session
$ ./server
Server PID: 4242
# In another terminal:
$ ./client 4242 "Hello, World!"

# Unicode example
./client 4242 "こんにちは 👋"

## 🛰️ Minitalk
This project demonstrates the use of Unix signals as a communication medium between two programs—the client and the server. By using signals (SIGUSR1 for 0 and SIGUSR2 for 1), the client encodes a message and sends it bit by bit to the server. When the server receives a bit, it sends back a handshake (acknowledgment) signal to the client to guarantee no data loss. Minitalk showcases a simple and robust inter-process data transfer through its handshake mechanism.

## Features
- supports unicode
- sends messagas without error

## 📚 Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Key Functions](#key-functions)
- [Requirements](#requirements)

  ## 📁 Project Structure

- `server.c` – Handles incoming signals and prints the received message.
- `client.c` – Sends the message bit by bit to the server.
- `libft/` – (If applicable) Custom implementations of common C functions.
- `Makefile` – Builds the client and server binaries.

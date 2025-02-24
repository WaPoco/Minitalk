# Minitalk
This project demonstrates the use of Unix signals as a communication medium between two programs - the client and the server. By using signals (SIGUSR1 to represent a binary 0 and SIGUSR2 to represent a binary 1) the client encodes a message and sends it bit by bit to the server. When the server receives a bit it sends back a signal to the client to assure no data loss.

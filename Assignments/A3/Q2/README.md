### Note

To run and test the programs correctly, always run P1 first and then P2 in different ttys.
Make sure you have sudo priviledges when running the programs.

### Functions used for functionality

Some important C functions and structs used for IPC functionality are:

    mkfifo()
    open(), write(), close()
    unlink()
    struct sockaddr_un
    socket()
    bind()
    listen()
    accept()

### Explanation
The FIFO-based programs exchange data with each other using named FIFO (first in first out) pipes. They need to have write and read priviledges to stream their data.

The Socket-based programs exchange data with each other using Sockets. P1 acts as the server while P2 acts as the client. Note that if the socket is not closed and unlinked using close() and unlink(), the socket will continue to run in the background.

The Shared memory based programs exchange data using shared memory which is the fastest way to share data among different processes.


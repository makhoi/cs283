1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The client knows a command's output is complete when the server sends an EOF marker (like 0x04). To handle partial reads, it should loop until EOF is received, using buffering and timeouts to ensure the full message is captured.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

Since TCP is a stream protocol, a shell must define message boundaries using delimiters (\n, 0x04) or length-prefixing. Without this, the client may read incomplete or merged responses, causing errors.

3. Describe the general differences between stateful and stateless protocols.

Stateful protocols keep track of session history (e.g., SSH), while stateless protocols treat each request independently (e.g., HTTP, DNS). Stateful is useful for continuous interactions, but stateless is more scalable.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

UDP is used when speed matters more than reliability, like in streaming, VoIP, and gaming. It avoids TCP’s overhead, and applications can handle packet loss themselves if needed.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The OS provides sockets, which let applications communicate over networks using system calls like socket(), send(), and recv(). This abstracts TCP/UDP communication for programs.
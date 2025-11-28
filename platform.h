#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef _WIN32
/* Windows platform */
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

/* Map POSIX types to Windows types */
typedef int socklen_t;

/* Map POSIX functions to Windows equivalents */
#define close(s) closesocket(s)
#define ioctl(s, cmd, arg) ioctlsocket(s, cmd, (u_long*)(arg))

/* Windows doesn't have these error codes in errno.h */
#ifndef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif
#ifndef EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#endif
#ifndef EAGAIN
#define EAGAIN WSAEWOULDBLOCK
#endif

/* Initialize Winsock */
static inline int platform_init(void) {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

static inline void platform_cleanup(void) {
    WSACleanup();
}

#else
/* POSIX platform (Linux, Android, etc.) */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

static inline int platform_init(void) {
    return 0;
}

static inline void platform_cleanup(void) {
}

#endif

#endif /* __PLATFORM_H__ */

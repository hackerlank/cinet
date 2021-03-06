#ifndef __PLATFORM_SOCKET_H__
#define __PLATFORM_SOCKET_H__

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/types.h>
#include <netinet/in.h> // base struct
#include <netinet/tcp.h> // tcp
#include <sys/socket.h> // base function
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h> // file handle
#endif

// windows only
#ifndef SOCKET_VERSION_REQUIRED
#define SOCKET_VERSION_REQUIRED     0x202
#endif

// windows has,linux no
#ifndef SOCKET
	#define SOCKET unsigned int
#endif

#ifndef INVALID_SOCKET
	#define INVALID_SOCKET (SOCKET)(~0)
#endif

#ifndef SOCKET_ERROR
	#define SOCKET_ERROR -1
#endif

#ifndef SOCKET_STREAM
	#define SOCKET_STREAM SOCK_STREAM
#endif

#ifndef ADDR_ANY
	#define ADDR_ANY INADDR_ANY
#endif

#endif

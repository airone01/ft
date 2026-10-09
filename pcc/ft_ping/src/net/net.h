#ifndef SRC_NET_NET_H
#define SRC_NET_NET_H

#include "../types.h"
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

/**
 * @brief Resolves a host
 *
 * @returns 0 on success, anything else otherwise
 */
int resolve_host(const CliOptions opts, struct sockaddr_in **target,
                 struct addrinfo **res, char ip_str[], int ipnmemb);

/**
 * @brief Prepares the main socket
 */
int prepare_sock(struct timeval timeout);

/**
 * @brief Main ping loop
 *
 * @returns 0 on success, 1 on loop break
 */
int ping_echo(uint16_t pid, int seq, int sock, struct sockaddr_in *target);

#endif /* SRC_NET_NET_H */

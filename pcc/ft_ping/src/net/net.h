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

int process_packet(char *buf, ssize_t len, uint16_t pid,
                   struct sockaddr_in *from, const CliOptions opts,
                   PingStats *stats);

/**
 * @brief Main polling program loop
 *
 * @returns -1 on timeout
 * @returns -2 on sigint
 */
int recv_echo_loop(int sock, uint16_t pid, const CliOptions opts,
                   PingStats *stats);

int send_echo(int sock, uint16_t pid, int seq, struct sockaddr_in *target,
              PingStats *stats);

long get_time_ms(void);

#endif /* SRC_NET_NET_H */

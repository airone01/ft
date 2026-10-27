# ft_ping

Re-implementation of inetutils' `ping` command.

## Socket Privileges

### Inetutil/Iputil's Ping Permissions Set Up

It's possible to create raw sockets without needing to elevate to root at each
execution, by simply giving the Setuid bit (`chmod u+s /path_to_ping`), or
adding the `CAT_NET_RAW` capability to the executable file
(`setcap cat_net_raw+ep /path_to_ping`, better).

### Unprivileged ICMP Sockets

Starting with Linux 3.0, the kernel introduced unprivileged ICMP datagram
sockets. Instead of `SOCK_RAW`, we can create a datagram socket specifically for
ICMP:

```c
socket(AFT_INET, SOCK_DGRAM, IPPROTO_ICMP);
```

The kernel restricts what an unprivileged `SOCK_DGRAM` ICMP socket can do:

- Send `ICMP_ECHO` only. Cannot send arbitrary ICMP types like Redirects or
  Router Advertisements.
- Cannot spoof IP header or manipulate raw fields.
- Address is controlled via a sysctl configuration:
  `sysctl net.ipv4.ping_group_range`. This is usually set large enough by
  default on most distros that any user can open unprivileged ICMP sockets.

Anyway, because switching from `SOCK_RAW` ro `SOCK_DGRAM` fundamentally alters
how packets are transmitted, received, and prepared, I will probably not do it.

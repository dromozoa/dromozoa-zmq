# zmq_getsockopt

Name|Type|Unit|Size|Default|Description
----|----|----|----|----|----
ZMQ_AFFINITY|uint64_t|N/A (bitmap)||0|Retrieve I/O thread affinity
ZMQ_BACKLOG|int|connections||100|Retrieve maximum length of the queue of outstanding connections
ZMQ_CONNECT_TIMEOUT|int|milliseconds||0 (disabled)|Retrieve connect() timeout
ZMQ_CURVE_PUBLICKEY|binary data or Z85 text string||32 or 41|null|Retrieve current CURVE public key
ZMQ_CURVE_SECRETKEY|binary data or Z85 text string||32 or 41|null|Retrieve current CURVE secret key
ZMQ_CURVE_SERVERKEY|binary data or Z85 text string||32 or 41|null|Retrieve current CURVE server key
ZMQ_EVENTS|int|N/A (flags)||N/A|Retrieve socket event state
ZMQ_FD|int on POSIX systems, SOCKET on Windows|N/A||N/A|Retrieve file descriptor associated with the socket
ZMQ_GSSAPI_PLAINTEXT|int|0, 1||0 (false)|Retrieve GSSAPI plaintext or encrypted status
ZMQ_GSSAPI_PRINCIPAL|NULL-terminated character string|N/A||null string|Retrieve the name of the GSSAPI principal
ZMQ_GSSAPI_SERVER|int|0, 1||0 (false)|Retrieve current GSSAPI server role
ZMQ_GSSAPI_SERVICE_PRINCIPAL|NULL-terminated character string|N/A||null string|Retrieve the name of the GSSAPI service principal
ZMQ_HANDSHAKE_IVL|int|milliseconds||30000|Retrieve maximum handshake interval
ZMQ_IDENTITY|binary data|N/A||NULL|Retrieve socket identity
ZMQ_IMMEDIATE|int|boolean||0 (false)|Retrieve attach-on-connect value
ZMQ_INVERT_MATCHING|int|0,1||0|Retrieve inverted filtering status
ZMQ_IPV4ONLY|int|boolean||1 (true)|Retrieve IPv4-only socket override status
ZMQ_IPV6|int|boolean||0 (false)|Retrieve IPv6 socket status
ZMQ_LAST_ENDPOINT|NULL-terminated character string|N/A||NULL|Retrieve the last endpoint set
ZMQ_LINGER|int|milliseconds||-1 (infinite)|Retrieve linger period for socket shutdown
ZMQ_MAXMSGSIZE|int64_t|bytes||-1|Maximum acceptable inbound message size
ZMQ_MECHANISM|int|ZMQ_NULL, ZMQ_PLAIN, ZMQ_CURVE, or ZMQ_GSSAPI||ZMQ_NULL|Retrieve current security mechanism
ZMQ_MULTICAST_HOPS|int|network hops||1|Maximum network hops for multicast packets
ZMQ_MULTICAST_MAXTPDU|int|bytes||1500|Maximum transport data unit size for multicast packets
ZMQ_PLAIN_PASSWORD|NULL-terminated character string|N/A||null string|Retrieve current password
ZMQ_PLAIN_SERVER|int|0, 1||int|Retrieve current PLAIN server role
ZMQ_PLAIN_USERNAME|NULL-terminated character string|N/A||null string|Retrieve current PLAIN username
ZMQ_USE_FD|int|file descriptor||-1|Retrieve the pre-allocated socket file descriptor
ZMQ_RATE|int|kilobits per second||100|Retrieve multicast data rate
ZMQ_RCVBUF|int|bytes||8192|Retrieve kernel receive buffer size
ZMQ_RCVHWM|int|messages||1000|Retrieve high water mark for inbound messages
ZMQ_RCVMORE|int|boolean||N/A|More message data parts to follow
ZMQ_RCVTIMEO|int|milliseconds||-1 (infinite)|Maximum time before a socket operation returns with EAGAIN
ZMQ_RECONNECT_IVL|int|milliseconds||100|Retrieve reconnection interval
ZMQ_RECONNECT_IVL_MAX|int|milliseconds||0 (only use ZMQ_RECONNECT_IVL)|Retrieve maximum reconnection interval
ZMQ_RECOVERY_IVL|int|milliseconds||10000|Get multicast recovery interval
ZMQ_SNDBUF|int|bytes||8192|Retrieve kernel transmit buffer size
ZMQ_SNDHWM|int|messages||1000|Retrieves high water mark for outbound messages
ZMQ_SNDTIMEO|int|milliseconds||-1 (infinite)|Maximum time before a socket operation returns with EAGAIN
ZMQ_SOCKS_PROXY|NULL-terminated character string|N/A||null string|Retrieve SOCKS5 proxy address
ZMQ_TCP_KEEPALIVE|int|-1,0,1||-1 (leave to OS default)|Override SO_KEEPALIVE socket option
ZMQ_TCP_KEEPALIVE_CNT|int|-1,>0||-1 (leave to OS default)|Override TCP_KEEPCNT socket option
ZMQ_TCP_KEEPALIVE_IDLE|int|-1,>0||-1 (leave to OS default)|Override TCP_KEEPIDLE (or TCP_KEEPALIVE on some OS)
ZMQ_TCP_KEEPALIVE_INTVL|int|-1,>0||-1 (leave to OS default)|Override TCP_KEEPINTVL socket option
ZMQ_TCP_MAXRT|int|milliseconds||0 (leave to OS default)|Retrieve Max TCP Retransmit Timeout
ZMQ_TOS|int|>0||0|Retrieve the Type-of-Service socket override status
ZMQ_TYPE|int|N/A||N/A|Retrieve socket type
ZMQ_ZAP_DOMAIN|character string|N/A||not set|Retrieve RFC 27 authentication domain
ZMQ_VMCI_BUFFER_SIZE|uint64_t|bytes||65546|Retrieve buffer size of the VMCI socket
ZMQ_VMCI_BUFFER_MIN_SIZE|uint64_t|bytes||128|Retrieve min buffer size of the VMCI socket
ZMQ_VMCI_BUFFER_MAX_SIZE|uint64_t|bytes||262144|Retrieve max buffer size of the VMCI socket
ZMQ_VMCI_CONNECT_TIMEOUT|int|milliseconds||-1|Retrieve connection timeout of the VMCI socket

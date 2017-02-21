# zmq_setsockopt

Name|Type|Unit|Size|Default|Description
----|----|----|----|----|----
ZMQ_AFFINITY|uint64_t|N/A (bitmap)||0|Set I/O thread affinity
ZMQ_BACKLOG|int|connections||100|Set maximum length of the queue of outstanding connections
ZMQ_CONNECT_RID|binary data|N/A||NULL|Assign the next outbound connection id 
ZMQ_CONFLATE|int|boolean||0 (false)|Keep only last message
ZMQ_CONNECT_TIMEOUT|int|milliseconds||0 (disabled)|Set connect() timeout
ZMQ_CURVE_PUBLICKEY|binary data or Z85 text string||32 or 41|NULL|Set CURVE public key
ZMQ_CURVE_SECRETKEY|binary data or Z85 text string||32 or 41|NULL|Set CURVE secret key
ZMQ_CURVE_SERVER|int|0, 1||0|Set CURVE server role
ZMQ_CURVE_SERVERKEY|binary data or Z85 text string||32 or 41|NULL|Set CURVE server key
ZMQ_GSSAPI_PLAINTEXT|int|0, 1||0 (false)|Disable GSSAPI encryption
ZMQ_GSSAPI_PRINCIPAL|character string|N/A||not set|Set name of GSSAPI principal
ZMQ_GSSAPI_SERVER|int|0, 1||0 (false)|Set GSSAPI server role
ZMQ_GSSAPI_SERVICE_PRINCIPAL|character string|N/A||not set|Set name of GSSAPI service principal
ZMQ_HANDSHAKE_IVL|int|milliseconds||30000|Set maximum handshake interval
ZMQ_HEARTBEAT_IVL|int|milliseconds||0|Set interval between sending ZMTP heartbeats
ZMQ_HEARTBEAT_TIMEOUT|int|milliseconds||0|Set timeout for ZMTP heartbeats
ZMQ_HEARTBEAT_TTL|int|milliseconds||0|Set the TTL value for ZMTP heartbeats
ZMQ_IDENTITY|binary data|N/A||NULL|Set socket identity
ZMQ_IMMEDIATE|int|boolean||0 (false)|Queue messages only to completed connections
ZMQ_INVERT_MATCHING|int|0,1||0|Invert message filtering
ZMQ_IPV6|int|boolean||0 (false)|Enable IPv6 on socket
ZMQ_LINGER|int|milliseconds||30000 (thirty seconds)|Set linger period for socket shutdown
ZMQ_MAXMSGSIZE|int64_t|bytes||-1|Maximum acceptable inbound message size
ZMQ_MULTICAST_HOPS|int|network hops||1|Maximum network hops for multicast packets
ZMQ_MULTICAST_MAXTPDU|int|bytes||1500|Maximum transport data unit size for multicast packets
ZMQ_PLAIN_PASSWORD|character string|N/A||not set|Set PLAIN security password
ZMQ_PLAIN_SERVER|int|0, 1||0|Set PLAIN server role
ZMQ_PLAIN_USERNAME|character string|N/A||not set|Set PLAIN security username
ZMQ_USE_FD|int|file descriptor||-1|Set the pre-allocated socket file descriptor
ZMQ_PROBE_ROUTER|int|0, 1||0|bootstrap connections to ROUTER sockets
ZMQ_RATE|int|kilobits per second||100|Set multicast data rate
ZMQ_RCVBUF|int|bytes||-1|Set kernel receive buffer size
ZMQ_RCVHWM|int|messages||1000|Set high water mark for inbound messages
ZMQ_RCVTIMEO|int|milliseconds||-1 (infinite)|Maximum time before a recv operation returns with EAGAIN
ZMQ_RECONNECT_IVL|int|milliseconds||100|Set reconnection interval
ZMQ_RECONNECT_IVL_MAX|int|milliseconds||0 (only use ZMQ_RECONNECT_IVL)|Set maximum reconnection interval
ZMQ_RECOVERY_IVL|int|milliseconds||10000|Set multicast recovery interval
ZMQ_REQ_CORRELATE|int|0, 1||0|match replies with requests
ZMQ_REQ_RELAXED|int|0, 1||0|relax strict alternation between request and reply
ZMQ_ROUTER_HANDOVER|int|0, 1||0|handle duplicate client identities on ROUTER sockets
ZMQ_ROUTER_MANDATORY|int|0, 1||0|accept only routable messages on ROUTER sockets
ZMQ_ROUTER_RAW|int|0, 1||0|switch ROUTER socket to raw mode
ZMQ_SNDBUF|int|bytes||-1|Set kernel transmit buffer size
ZMQ_SNDHWM|int|messages||1000|Set high water mark for outbound messages
ZMQ_SNDTIMEO|int|milliseconds||-1 (infinite)|Maximum time before a send operation returns with EAGAIN
ZMQ_SOCKS_PROXY|character string|N/A||not set|Set SOCKS5 proxy address
ZMQ_STREAM_NOTIFY|int|0, 1||1|send connect and disconnect notifications
ZMQ_SUBSCRIBE|binary data|N/A||N/A|Establish message filter
ZMQ_TCP_KEEPALIVE|int|-1,0,1||-1 (leave to OS default)|Override SO_KEEPALIVE socket option
ZMQ_TCP_KEEPALIVE_CNT|int|-1,>0||-1 (leave to OS default)|Override TCP_KEEPCNT socket option
ZMQ_TCP_KEEPALIVE_IDLE|int|-1,>0||-1 (leave to OS default)|Override TCP_KEEPIDLE (or TCP_KEEPALIVE on some OS)
ZMQ_TCP_KEEPALIVE_INTVL|int|-1,>0||-1 (leave to OS default)|Override TCP_KEEPINTVL socket option
ZMQ_TCP_MAXRT|int|milliseconds||0 (leave to OS default)|Set TCP Maximum Retransmit Timeout
ZMQ_TOS|int|>0||0|Set the Type-of-Service on socket
ZMQ_UNSUBSCRIBE|binary data|N/A||N/A|Remove message filter
ZMQ_XPUB_VERBOSE|int|0, 1||0|pass subscribe messages on XPUB socket
ZMQ_XPUB_VERBOSER|int|0, 1||0|pass subscribe and unsubscribe messages on XPUB socket
ZMQ_XPUB_MANUAL|int|0, 1||0|change the subscription handling to manual
ZMQ_XPUB_NODROP|int|0, 1||0|do not silently drop messages if SENDHWM is reached
ZMQ_XPUB_WELCOME_MSG|binary data|N/A||NULL|set welcome message that will be received by subscriber when connecting
ZMQ_ZAP_DOMAIN|character string|N/A||not set|Set RFC 27 authentication domain
ZMQ_TCP_ACCEPT_FILTER|binary data|N/A||no filters (allow from all)|Assign filters to allow new TCP connections
ZMQ_IPC_FILTER_GID|gid_t|N/A||no filters (allow from all)|Assign group ID filters to allow new IPC connections
ZMQ_IPC_FILTER_PID|pid_t|N/A||no filters (allow from all)|Assign process ID filters to allow new IPC connections
ZMQ_IPC_FILTER_UID|uid_t|N/A||no filters (allow from all)|Assign user ID filters to allow new IPC connections
ZMQ_IPV4ONLY|int|boolean||1 (true)|Use IPv4-only on socket
ZMQ_VMCI_BUFFER_SIZE|uint64_t|bytes||65546|Set buffer size of the VMCI socket
ZMQ_VMCI_BUFFER_MIN_SIZE|uint64_t|bytes||128|Set min buffer size of the VMCI socket
ZMQ_VMCI_BUFFER_MAX_SIZE|uint64_t|bytes||262144|Set max buffer size of the VMCI socket
ZMQ_VMCI_CONNECT_TIMEOUT|int|milliseconds||-1|Set connection timeout of the VMCI socket

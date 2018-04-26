#include "common.hpp"
#include "symbols.hpp"

namespace dromozoa {
  void initialize_symbols(lua_State* L) {
#ifdef ZMQ_VERSION_MAJOR
    luaX_set_field(L, -1, "ZMQ_VERSION_MAJOR", ZMQ_VERSION_MAJOR);
#endif
#ifdef ZMQ_VERSION_MINOR
    luaX_set_field(L, -1, "ZMQ_VERSION_MINOR", ZMQ_VERSION_MINOR);
#endif
#ifdef ZMQ_VERSION_PATCH
    luaX_set_field(L, -1, "ZMQ_VERSION_PATCH", ZMQ_VERSION_PATCH);
#endif
#ifdef ZMQ_VERSION
    luaX_set_field(L, -1, "ZMQ_VERSION", ZMQ_VERSION);
#endif
#ifdef ZMQ_DEFINED_STDINT
    luaX_set_field(L, -1, "ZMQ_DEFINED_STDINT", ZMQ_DEFINED_STDINT);
#endif
#ifdef ZMQ_HAUSNUMERO
    luaX_set_field(L, -1, "ZMQ_HAUSNUMERO", ZMQ_HAUSNUMERO);
#endif
#ifdef ZMQ_IO_THREADS
    luaX_set_field(L, -1, "ZMQ_IO_THREADS", ZMQ_IO_THREADS);
#endif
#ifdef ZMQ_MAX_SOCKETS
    luaX_set_field(L, -1, "ZMQ_MAX_SOCKETS", ZMQ_MAX_SOCKETS);
#endif
#ifdef ZMQ_SOCKET_LIMIT
    luaX_set_field(L, -1, "ZMQ_SOCKET_LIMIT", ZMQ_SOCKET_LIMIT);
#endif
#ifdef ZMQ_THREAD_PRIORITY
    luaX_set_field(L, -1, "ZMQ_THREAD_PRIORITY", ZMQ_THREAD_PRIORITY);
#endif
#ifdef ZMQ_THREAD_SCHED_POLICY
    luaX_set_field(L, -1, "ZMQ_THREAD_SCHED_POLICY", ZMQ_THREAD_SCHED_POLICY);
#endif
#ifdef ZMQ_MAX_MSGSZ
    luaX_set_field(L, -1, "ZMQ_MAX_MSGSZ", ZMQ_MAX_MSGSZ);
#endif
#ifdef ZMQ_IO_THREADS_DFLT
    luaX_set_field(L, -1, "ZMQ_IO_THREADS_DFLT", ZMQ_IO_THREADS_DFLT);
#endif
#ifdef ZMQ_MAX_SOCKETS_DFLT
    luaX_set_field(L, -1, "ZMQ_MAX_SOCKETS_DFLT", ZMQ_MAX_SOCKETS_DFLT);
#endif
#ifdef ZMQ_THREAD_PRIORITY_DFLT
    luaX_set_field(L, -1, "ZMQ_THREAD_PRIORITY_DFLT", ZMQ_THREAD_PRIORITY_DFLT);
#endif
#ifdef ZMQ_THREAD_SCHED_POLICY_DFLT
    luaX_set_field(L, -1, "ZMQ_THREAD_SCHED_POLICY_DFLT", ZMQ_THREAD_SCHED_POLICY_DFLT);
#endif
#ifdef ZMQ_PAIR
    luaX_set_field(L, -1, "ZMQ_PAIR", ZMQ_PAIR);
#endif
#ifdef ZMQ_PUB
    luaX_set_field(L, -1, "ZMQ_PUB", ZMQ_PUB);
#endif
#ifdef ZMQ_SUB
    luaX_set_field(L, -1, "ZMQ_SUB", ZMQ_SUB);
#endif
#ifdef ZMQ_REQ
    luaX_set_field(L, -1, "ZMQ_REQ", ZMQ_REQ);
#endif
#ifdef ZMQ_REP
    luaX_set_field(L, -1, "ZMQ_REP", ZMQ_REP);
#endif
#ifdef ZMQ_DEALER
    luaX_set_field(L, -1, "ZMQ_DEALER", ZMQ_DEALER);
#endif
#ifdef ZMQ_ROUTER
    luaX_set_field(L, -1, "ZMQ_ROUTER", ZMQ_ROUTER);
#endif
#ifdef ZMQ_PULL
    luaX_set_field(L, -1, "ZMQ_PULL", ZMQ_PULL);
#endif
#ifdef ZMQ_PUSH
    luaX_set_field(L, -1, "ZMQ_PUSH", ZMQ_PUSH);
#endif
#ifdef ZMQ_XPUB
    luaX_set_field(L, -1, "ZMQ_XPUB", ZMQ_XPUB);
#endif
#ifdef ZMQ_XSUB
    luaX_set_field(L, -1, "ZMQ_XSUB", ZMQ_XSUB);
#endif
#ifdef ZMQ_STREAM
    luaX_set_field(L, -1, "ZMQ_STREAM", ZMQ_STREAM);
#endif
#ifdef ZMQ_XREQ
    luaX_set_field(L, -1, "ZMQ_XREQ", ZMQ_XREQ);
#endif
#ifdef ZMQ_XREP
    luaX_set_field(L, -1, "ZMQ_XREP", ZMQ_XREP);
#endif
#ifdef ZMQ_AFFINITY
    luaX_set_field(L, -1, "ZMQ_AFFINITY", ZMQ_AFFINITY);
#endif
#ifdef ZMQ_ROUTING_ID
    luaX_set_field(L, -1, "ZMQ_ROUTING_ID", ZMQ_ROUTING_ID);
#endif
#ifdef ZMQ_SUBSCRIBE
    luaX_set_field(L, -1, "ZMQ_SUBSCRIBE", ZMQ_SUBSCRIBE);
#endif
#ifdef ZMQ_UNSUBSCRIBE
    luaX_set_field(L, -1, "ZMQ_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
#endif
#ifdef ZMQ_RATE
    luaX_set_field(L, -1, "ZMQ_RATE", ZMQ_RATE);
#endif
#ifdef ZMQ_RECOVERY_IVL
    luaX_set_field(L, -1, "ZMQ_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
#endif
#ifdef ZMQ_SNDBUF
    luaX_set_field(L, -1, "ZMQ_SNDBUF", ZMQ_SNDBUF);
#endif
#ifdef ZMQ_RCVBUF
    luaX_set_field(L, -1, "ZMQ_RCVBUF", ZMQ_RCVBUF);
#endif
#ifdef ZMQ_RCVMORE
    luaX_set_field(L, -1, "ZMQ_RCVMORE", ZMQ_RCVMORE);
#endif
#ifdef ZMQ_FD
    luaX_set_field(L, -1, "ZMQ_FD", ZMQ_FD);
#endif
#ifdef ZMQ_EVENTS
    luaX_set_field(L, -1, "ZMQ_EVENTS", ZMQ_EVENTS);
#endif
#ifdef ZMQ_TYPE
    luaX_set_field(L, -1, "ZMQ_TYPE", ZMQ_TYPE);
#endif
#ifdef ZMQ_LINGER
    luaX_set_field(L, -1, "ZMQ_LINGER", ZMQ_LINGER);
#endif
#ifdef ZMQ_RECONNECT_IVL
    luaX_set_field(L, -1, "ZMQ_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
#endif
#ifdef ZMQ_BACKLOG
    luaX_set_field(L, -1, "ZMQ_BACKLOG", ZMQ_BACKLOG);
#endif
#ifdef ZMQ_RECONNECT_IVL_MAX
    luaX_set_field(L, -1, "ZMQ_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
#endif
#ifdef ZMQ_MAXMSGSIZE
    luaX_set_field(L, -1, "ZMQ_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
#endif
#ifdef ZMQ_SNDHWM
    luaX_set_field(L, -1, "ZMQ_SNDHWM", ZMQ_SNDHWM);
#endif
#ifdef ZMQ_RCVHWM
    luaX_set_field(L, -1, "ZMQ_RCVHWM", ZMQ_RCVHWM);
#endif
#ifdef ZMQ_MULTICAST_HOPS
    luaX_set_field(L, -1, "ZMQ_MULTICAST_HOPS", ZMQ_MULTICAST_HOPS);
#endif
#ifdef ZMQ_RCVTIMEO
    luaX_set_field(L, -1, "ZMQ_RCVTIMEO", ZMQ_RCVTIMEO);
#endif
#ifdef ZMQ_SNDTIMEO
    luaX_set_field(L, -1, "ZMQ_SNDTIMEO", ZMQ_SNDTIMEO);
#endif
#ifdef ZMQ_LAST_ENDPOINT
    luaX_set_field(L, -1, "ZMQ_LAST_ENDPOINT", ZMQ_LAST_ENDPOINT);
#endif
#ifdef ZMQ_ROUTER_MANDATORY
    luaX_set_field(L, -1, "ZMQ_ROUTER_MANDATORY", ZMQ_ROUTER_MANDATORY);
#endif
#ifdef ZMQ_TCP_KEEPALIVE
    luaX_set_field(L, -1, "ZMQ_TCP_KEEPALIVE", ZMQ_TCP_KEEPALIVE);
#endif
#ifdef ZMQ_TCP_KEEPALIVE_CNT
    luaX_set_field(L, -1, "ZMQ_TCP_KEEPALIVE_CNT", ZMQ_TCP_KEEPALIVE_CNT);
#endif
#ifdef ZMQ_TCP_KEEPALIVE_IDLE
    luaX_set_field(L, -1, "ZMQ_TCP_KEEPALIVE_IDLE", ZMQ_TCP_KEEPALIVE_IDLE);
#endif
#ifdef ZMQ_TCP_KEEPALIVE_INTVL
    luaX_set_field(L, -1, "ZMQ_TCP_KEEPALIVE_INTVL", ZMQ_TCP_KEEPALIVE_INTVL);
#endif
#ifdef ZMQ_IMMEDIATE
    luaX_set_field(L, -1, "ZMQ_IMMEDIATE", ZMQ_IMMEDIATE);
#endif
#ifdef ZMQ_XPUB_VERBOSE
    luaX_set_field(L, -1, "ZMQ_XPUB_VERBOSE", ZMQ_XPUB_VERBOSE);
#endif
#ifdef ZMQ_ROUTER_RAW
    luaX_set_field(L, -1, "ZMQ_ROUTER_RAW", ZMQ_ROUTER_RAW);
#endif
#ifdef ZMQ_IPV6
    luaX_set_field(L, -1, "ZMQ_IPV6", ZMQ_IPV6);
#endif
#ifdef ZMQ_MECHANISM
    luaX_set_field(L, -1, "ZMQ_MECHANISM", ZMQ_MECHANISM);
#endif
#ifdef ZMQ_PLAIN_SERVER
    luaX_set_field(L, -1, "ZMQ_PLAIN_SERVER", ZMQ_PLAIN_SERVER);
#endif
#ifdef ZMQ_PLAIN_USERNAME
    luaX_set_field(L, -1, "ZMQ_PLAIN_USERNAME", ZMQ_PLAIN_USERNAME);
#endif
#ifdef ZMQ_PLAIN_PASSWORD
    luaX_set_field(L, -1, "ZMQ_PLAIN_PASSWORD", ZMQ_PLAIN_PASSWORD);
#endif
#ifdef ZMQ_CURVE_SERVER
    luaX_set_field(L, -1, "ZMQ_CURVE_SERVER", ZMQ_CURVE_SERVER);
#endif
#ifdef ZMQ_CURVE_PUBLICKEY
    luaX_set_field(L, -1, "ZMQ_CURVE_PUBLICKEY", ZMQ_CURVE_PUBLICKEY);
#endif
#ifdef ZMQ_CURVE_SECRETKEY
    luaX_set_field(L, -1, "ZMQ_CURVE_SECRETKEY", ZMQ_CURVE_SECRETKEY);
#endif
#ifdef ZMQ_CURVE_SERVERKEY
    luaX_set_field(L, -1, "ZMQ_CURVE_SERVERKEY", ZMQ_CURVE_SERVERKEY);
#endif
#ifdef ZMQ_PROBE_ROUTER
    luaX_set_field(L, -1, "ZMQ_PROBE_ROUTER", ZMQ_PROBE_ROUTER);
#endif
#ifdef ZMQ_REQ_CORRELATE
    luaX_set_field(L, -1, "ZMQ_REQ_CORRELATE", ZMQ_REQ_CORRELATE);
#endif
#ifdef ZMQ_REQ_RELAXED
    luaX_set_field(L, -1, "ZMQ_REQ_RELAXED", ZMQ_REQ_RELAXED);
#endif
#ifdef ZMQ_CONFLATE
    luaX_set_field(L, -1, "ZMQ_CONFLATE", ZMQ_CONFLATE);
#endif
#ifdef ZMQ_ZAP_DOMAIN
    luaX_set_field(L, -1, "ZMQ_ZAP_DOMAIN", ZMQ_ZAP_DOMAIN);
#endif
#ifdef ZMQ_ROUTER_HANDOVER
    luaX_set_field(L, -1, "ZMQ_ROUTER_HANDOVER", ZMQ_ROUTER_HANDOVER);
#endif
#ifdef ZMQ_TOS
    luaX_set_field(L, -1, "ZMQ_TOS", ZMQ_TOS);
#endif
#ifdef ZMQ_CONNECT_ROUTING_ID
    luaX_set_field(L, -1, "ZMQ_CONNECT_ROUTING_ID", ZMQ_CONNECT_ROUTING_ID);
#endif
#ifdef ZMQ_GSSAPI_SERVER
    luaX_set_field(L, -1, "ZMQ_GSSAPI_SERVER", ZMQ_GSSAPI_SERVER);
#endif
#ifdef ZMQ_GSSAPI_PRINCIPAL
    luaX_set_field(L, -1, "ZMQ_GSSAPI_PRINCIPAL", ZMQ_GSSAPI_PRINCIPAL);
#endif
#ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL
    luaX_set_field(L, -1, "ZMQ_GSSAPI_SERVICE_PRINCIPAL", ZMQ_GSSAPI_SERVICE_PRINCIPAL);
#endif
#ifdef ZMQ_GSSAPI_PLAINTEXT
    luaX_set_field(L, -1, "ZMQ_GSSAPI_PLAINTEXT", ZMQ_GSSAPI_PLAINTEXT);
#endif
#ifdef ZMQ_HANDSHAKE_IVL
    luaX_set_field(L, -1, "ZMQ_HANDSHAKE_IVL", ZMQ_HANDSHAKE_IVL);
#endif
#ifdef ZMQ_SOCKS_PROXY
    luaX_set_field(L, -1, "ZMQ_SOCKS_PROXY", ZMQ_SOCKS_PROXY);
#endif
#ifdef ZMQ_XPUB_NODROP
    luaX_set_field(L, -1, "ZMQ_XPUB_NODROP", ZMQ_XPUB_NODROP);
#endif
#ifdef ZMQ_BLOCKY
    luaX_set_field(L, -1, "ZMQ_BLOCKY", ZMQ_BLOCKY);
#endif
#ifdef ZMQ_XPUB_MANUAL
    luaX_set_field(L, -1, "ZMQ_XPUB_MANUAL", ZMQ_XPUB_MANUAL);
#endif
#ifdef ZMQ_XPUB_WELCOME_MSG
    luaX_set_field(L, -1, "ZMQ_XPUB_WELCOME_MSG", ZMQ_XPUB_WELCOME_MSG);
#endif
#ifdef ZMQ_STREAM_NOTIFY
    luaX_set_field(L, -1, "ZMQ_STREAM_NOTIFY", ZMQ_STREAM_NOTIFY);
#endif
#ifdef ZMQ_INVERT_MATCHING
    luaX_set_field(L, -1, "ZMQ_INVERT_MATCHING", ZMQ_INVERT_MATCHING);
#endif
#ifdef ZMQ_HEARTBEAT_IVL
    luaX_set_field(L, -1, "ZMQ_HEARTBEAT_IVL", ZMQ_HEARTBEAT_IVL);
#endif
#ifdef ZMQ_HEARTBEAT_TTL
    luaX_set_field(L, -1, "ZMQ_HEARTBEAT_TTL", ZMQ_HEARTBEAT_TTL);
#endif
#ifdef ZMQ_HEARTBEAT_TIMEOUT
    luaX_set_field(L, -1, "ZMQ_HEARTBEAT_TIMEOUT", ZMQ_HEARTBEAT_TIMEOUT);
#endif
#ifdef ZMQ_XPUB_VERBOSER
    luaX_set_field(L, -1, "ZMQ_XPUB_VERBOSER", ZMQ_XPUB_VERBOSER);
#endif
#ifdef ZMQ_CONNECT_TIMEOUT
    luaX_set_field(L, -1, "ZMQ_CONNECT_TIMEOUT", ZMQ_CONNECT_TIMEOUT);
#endif
#ifdef ZMQ_TCP_MAXRT
    luaX_set_field(L, -1, "ZMQ_TCP_MAXRT", ZMQ_TCP_MAXRT);
#endif
#ifdef ZMQ_THREAD_SAFE
    luaX_set_field(L, -1, "ZMQ_THREAD_SAFE", ZMQ_THREAD_SAFE);
#endif
#ifdef ZMQ_MULTICAST_MAXTPDU
    luaX_set_field(L, -1, "ZMQ_MULTICAST_MAXTPDU", ZMQ_MULTICAST_MAXTPDU);
#endif
#ifdef ZMQ_VMCI_BUFFER_SIZE
    luaX_set_field(L, -1, "ZMQ_VMCI_BUFFER_SIZE", ZMQ_VMCI_BUFFER_SIZE);
#endif
#ifdef ZMQ_VMCI_BUFFER_MIN_SIZE
    luaX_set_field(L, -1, "ZMQ_VMCI_BUFFER_MIN_SIZE", ZMQ_VMCI_BUFFER_MIN_SIZE);
#endif
#ifdef ZMQ_VMCI_BUFFER_MAX_SIZE
    luaX_set_field(L, -1, "ZMQ_VMCI_BUFFER_MAX_SIZE", ZMQ_VMCI_BUFFER_MAX_SIZE);
#endif
#ifdef ZMQ_VMCI_CONNECT_TIMEOUT
    luaX_set_field(L, -1, "ZMQ_VMCI_CONNECT_TIMEOUT", ZMQ_VMCI_CONNECT_TIMEOUT);
#endif
#ifdef ZMQ_USE_FD
    luaX_set_field(L, -1, "ZMQ_USE_FD", ZMQ_USE_FD);
#endif
#ifdef ZMQ_MORE
    luaX_set_field(L, -1, "ZMQ_MORE", ZMQ_MORE);
#endif
#ifdef ZMQ_SHARED
    luaX_set_field(L, -1, "ZMQ_SHARED", ZMQ_SHARED);
#endif
#ifdef ZMQ_DONTWAIT
    luaX_set_field(L, -1, "ZMQ_DONTWAIT", ZMQ_DONTWAIT);
#endif
#ifdef ZMQ_SNDMORE
    luaX_set_field(L, -1, "ZMQ_SNDMORE", ZMQ_SNDMORE);
#endif
#ifdef ZMQ_NULL
    luaX_set_field(L, -1, "ZMQ_NULL", ZMQ_NULL);
#endif
#ifdef ZMQ_PLAIN
    luaX_set_field(L, -1, "ZMQ_PLAIN", ZMQ_PLAIN);
#endif
#ifdef ZMQ_CURVE
    luaX_set_field(L, -1, "ZMQ_CURVE", ZMQ_CURVE);
#endif
#ifdef ZMQ_GSSAPI
    luaX_set_field(L, -1, "ZMQ_GSSAPI", ZMQ_GSSAPI);
#endif
#ifdef ZMQ_GROUP_MAX_LENGTH
    luaX_set_field(L, -1, "ZMQ_GROUP_MAX_LENGTH", ZMQ_GROUP_MAX_LENGTH);
#endif
#ifdef ZMQ_IDENTITY
    luaX_set_field(L, -1, "ZMQ_IDENTITY", ZMQ_IDENTITY);
#endif
#ifdef ZMQ_CONNECT_RID
    luaX_set_field(L, -1, "ZMQ_CONNECT_RID", ZMQ_CONNECT_RID);
#endif
#ifdef ZMQ_TCP_ACCEPT_FILTER
    luaX_set_field(L, -1, "ZMQ_TCP_ACCEPT_FILTER", ZMQ_TCP_ACCEPT_FILTER);
#endif
#ifdef ZMQ_IPC_FILTER_PID
    luaX_set_field(L, -1, "ZMQ_IPC_FILTER_PID", ZMQ_IPC_FILTER_PID);
#endif
#ifdef ZMQ_IPC_FILTER_UID
    luaX_set_field(L, -1, "ZMQ_IPC_FILTER_UID", ZMQ_IPC_FILTER_UID);
#endif
#ifdef ZMQ_IPC_FILTER_GID
    luaX_set_field(L, -1, "ZMQ_IPC_FILTER_GID", ZMQ_IPC_FILTER_GID);
#endif
#ifdef ZMQ_IPV4ONLY
    luaX_set_field(L, -1, "ZMQ_IPV4ONLY", ZMQ_IPV4ONLY);
#endif
#ifdef ZMQ_DELAY_ATTACH_ON_CONNECT
    luaX_set_field(L, -1, "ZMQ_DELAY_ATTACH_ON_CONNECT", ZMQ_DELAY_ATTACH_ON_CONNECT);
#endif
#ifdef ZMQ_NOBLOCK
    luaX_set_field(L, -1, "ZMQ_NOBLOCK", ZMQ_NOBLOCK);
#endif
#ifdef ZMQ_FAIL_UNROUTABLE
    luaX_set_field(L, -1, "ZMQ_FAIL_UNROUTABLE", ZMQ_FAIL_UNROUTABLE);
#endif
#ifdef ZMQ_ROUTER_BEHAVIOR
    luaX_set_field(L, -1, "ZMQ_ROUTER_BEHAVIOR", ZMQ_ROUTER_BEHAVIOR);
#endif
#ifdef ZMQ_SRCFD
    luaX_set_field(L, -1, "ZMQ_SRCFD", ZMQ_SRCFD);
#endif
#ifdef ZMQ_EVENT_CONNECTED
    luaX_set_field(L, -1, "ZMQ_EVENT_CONNECTED", ZMQ_EVENT_CONNECTED);
#endif
#ifdef ZMQ_EVENT_CONNECT_DELAYED
    luaX_set_field(L, -1, "ZMQ_EVENT_CONNECT_DELAYED", ZMQ_EVENT_CONNECT_DELAYED);
#endif
#ifdef ZMQ_EVENT_CONNECT_RETRIED
    luaX_set_field(L, -1, "ZMQ_EVENT_CONNECT_RETRIED", ZMQ_EVENT_CONNECT_RETRIED);
#endif
#ifdef ZMQ_EVENT_LISTENING
    luaX_set_field(L, -1, "ZMQ_EVENT_LISTENING", ZMQ_EVENT_LISTENING);
#endif
#ifdef ZMQ_EVENT_BIND_FAILED
    luaX_set_field(L, -1, "ZMQ_EVENT_BIND_FAILED", ZMQ_EVENT_BIND_FAILED);
#endif
#ifdef ZMQ_EVENT_ACCEPTED
    luaX_set_field(L, -1, "ZMQ_EVENT_ACCEPTED", ZMQ_EVENT_ACCEPTED);
#endif
#ifdef ZMQ_EVENT_ACCEPT_FAILED
    luaX_set_field(L, -1, "ZMQ_EVENT_ACCEPT_FAILED", ZMQ_EVENT_ACCEPT_FAILED);
#endif
#ifdef ZMQ_EVENT_CLOSED
    luaX_set_field(L, -1, "ZMQ_EVENT_CLOSED", ZMQ_EVENT_CLOSED);
#endif
#ifdef ZMQ_EVENT_CLOSE_FAILED
    luaX_set_field(L, -1, "ZMQ_EVENT_CLOSE_FAILED", ZMQ_EVENT_CLOSE_FAILED);
#endif
#ifdef ZMQ_EVENT_DISCONNECTED
    luaX_set_field(L, -1, "ZMQ_EVENT_DISCONNECTED", ZMQ_EVENT_DISCONNECTED);
#endif
#ifdef ZMQ_EVENT_MONITOR_STOPPED
    luaX_set_field(L, -1, "ZMQ_EVENT_MONITOR_STOPPED", ZMQ_EVENT_MONITOR_STOPPED);
#endif
#ifdef ZMQ_EVENT_ALL
    luaX_set_field(L, -1, "ZMQ_EVENT_ALL", ZMQ_EVENT_ALL);
#endif
#ifdef ZMQ_POLLIN
    luaX_set_field(L, -1, "ZMQ_POLLIN", ZMQ_POLLIN);
#endif
#ifdef ZMQ_POLLOUT
    luaX_set_field(L, -1, "ZMQ_POLLOUT", ZMQ_POLLOUT);
#endif
#ifdef ZMQ_POLLERR
    luaX_set_field(L, -1, "ZMQ_POLLERR", ZMQ_POLLERR);
#endif
#ifdef ZMQ_POLLPRI
    luaX_set_field(L, -1, "ZMQ_POLLPRI", ZMQ_POLLPRI);
#endif
#ifdef ZMQ_POLLITEMS_DFLT
    luaX_set_field(L, -1, "ZMQ_POLLITEMS_DFLT", ZMQ_POLLITEMS_DFLT);
#endif
#ifdef ZMQ_HAS_CAPABILITIES
    luaX_set_field(L, -1, "ZMQ_HAS_CAPABILITIES", ZMQ_HAS_CAPABILITIES);
#endif
#ifdef ZMQ_STREAMER
    luaX_set_field(L, -1, "ZMQ_STREAMER", ZMQ_STREAMER);
#endif
#ifdef ZMQ_FORWARDER
    luaX_set_field(L, -1, "ZMQ_FORWARDER", ZMQ_FORWARDER);
#endif
#ifdef ZMQ_QUEUE
    luaX_set_field(L, -1, "ZMQ_QUEUE", ZMQ_QUEUE);
#endif
#ifdef ZMQ_SERVER
    luaX_set_field(L, -1, "ZMQ_SERVER", ZMQ_SERVER);
#endif
#ifdef ZMQ_CLIENT
    luaX_set_field(L, -1, "ZMQ_CLIENT", ZMQ_CLIENT);
#endif
#ifdef ZMQ_RADIO
    luaX_set_field(L, -1, "ZMQ_RADIO", ZMQ_RADIO);
#endif
#ifdef ZMQ_DISH
    luaX_set_field(L, -1, "ZMQ_DISH", ZMQ_DISH);
#endif
#ifdef ZMQ_GATHER
    luaX_set_field(L, -1, "ZMQ_GATHER", ZMQ_GATHER);
#endif
#ifdef ZMQ_SCATTER
    luaX_set_field(L, -1, "ZMQ_SCATTER", ZMQ_SCATTER);
#endif
#ifdef ZMQ_DGRAM
    luaX_set_field(L, -1, "ZMQ_DGRAM", ZMQ_DGRAM);
#endif
#ifdef ZMQ_GSSAPI_PRINCIPAL_NAMETYPE
    luaX_set_field(L, -1, "ZMQ_GSSAPI_PRINCIPAL_NAMETYPE", ZMQ_GSSAPI_PRINCIPAL_NAMETYPE);
#endif
#ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE
    luaX_set_field(L, -1, "ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE", ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE);
#endif
#ifdef ZMQ_BINDTODEVICE
    luaX_set_field(L, -1, "ZMQ_BINDTODEVICE", ZMQ_BINDTODEVICE);
#endif
#ifdef ZMQ_ZAP_ENFORCE_DOMAIN
    luaX_set_field(L, -1, "ZMQ_ZAP_ENFORCE_DOMAIN", ZMQ_ZAP_ENFORCE_DOMAIN);
#endif
#ifdef ZMQ_EVENT_HANDSHAKE_FAILED_NO_DETAIL
    luaX_set_field(L, -1, "ZMQ_EVENT_HANDSHAKE_FAILED_NO_DETAIL", ZMQ_EVENT_HANDSHAKE_FAILED_NO_DETAIL);
#endif
#ifdef ZMQ_EVENT_HANDSHAKE_SUCCEEDED
    luaX_set_field(L, -1, "ZMQ_EVENT_HANDSHAKE_SUCCEEDED", ZMQ_EVENT_HANDSHAKE_SUCCEEDED);
#endif
#ifdef ZMQ_EVENT_HANDSHAKE_FAILED_PROTOCOL
    luaX_set_field(L, -1, "ZMQ_EVENT_HANDSHAKE_FAILED_PROTOCOL", ZMQ_EVENT_HANDSHAKE_FAILED_PROTOCOL);
#endif
#ifdef ZMQ_EVENT_HANDSHAKE_FAILED_AUTH
    luaX_set_field(L, -1, "ZMQ_EVENT_HANDSHAKE_FAILED_AUTH", ZMQ_EVENT_HANDSHAKE_FAILED_AUTH);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_UNSPECIFIED
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_UNSPECIFIED", ZMQ_PROTOCOL_ERROR_ZMTP_UNSPECIFIED);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_UNEXPECTED_COMMAND
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_UNEXPECTED_COMMAND", ZMQ_PROTOCOL_ERROR_ZMTP_UNEXPECTED_COMMAND);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_INVALID_SEQUENCE
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_INVALID_SEQUENCE", ZMQ_PROTOCOL_ERROR_ZMTP_INVALID_SEQUENCE);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_KEY_EXCHANGE
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_KEY_EXCHANGE", ZMQ_PROTOCOL_ERROR_ZMTP_KEY_EXCHANGE);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_UNSPECIFIED
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_UNSPECIFIED", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_UNSPECIFIED);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_MESSAGE
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_MESSAGE", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_MESSAGE);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_HELLO
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_HELLO", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_HELLO);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_INITIATE
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_INITIATE", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_INITIATE);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_ERROR
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_ERROR", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_ERROR);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_READY
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_READY", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_READY);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_WELCOME
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_WELCOME", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_WELCOME);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_INVALID_METADATA
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_INVALID_METADATA", ZMQ_PROTOCOL_ERROR_ZMTP_INVALID_METADATA);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_CRYPTOGRAPHIC
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_CRYPTOGRAPHIC", ZMQ_PROTOCOL_ERROR_ZMTP_CRYPTOGRAPHIC);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZMTP_MECHANISM_MISMATCH
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZMTP_MECHANISM_MISMATCH", ZMQ_PROTOCOL_ERROR_ZMTP_MECHANISM_MISMATCH);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZAP_UNSPECIFIED
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZAP_UNSPECIFIED", ZMQ_PROTOCOL_ERROR_ZAP_UNSPECIFIED);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZAP_MALFORMED_REPLY
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZAP_MALFORMED_REPLY", ZMQ_PROTOCOL_ERROR_ZAP_MALFORMED_REPLY);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZAP_BAD_REQUEST_ID
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZAP_BAD_REQUEST_ID", ZMQ_PROTOCOL_ERROR_ZAP_BAD_REQUEST_ID);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZAP_BAD_VERSION
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZAP_BAD_VERSION", ZMQ_PROTOCOL_ERROR_ZAP_BAD_VERSION);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZAP_INVALID_STATUS_CODE
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZAP_INVALID_STATUS_CODE", ZMQ_PROTOCOL_ERROR_ZAP_INVALID_STATUS_CODE);
#endif
#ifdef ZMQ_PROTOCOL_ERROR_ZAP_INVALID_METADATA
    luaX_set_field(L, -1, "ZMQ_PROTOCOL_ERROR_ZAP_INVALID_METADATA", ZMQ_PROTOCOL_ERROR_ZAP_INVALID_METADATA);
#endif
#ifdef ZMQ_MSG_T_SIZE
    luaX_set_field(L, -1, "ZMQ_MSG_T_SIZE", ZMQ_MSG_T_SIZE);
#endif
#ifdef ZMQ_THREAD_AFFINITY_CPU_ADD
    luaX_set_field(L, -1, "ZMQ_THREAD_AFFINITY_CPU_ADD", ZMQ_THREAD_AFFINITY_CPU_ADD);
#endif
#ifdef ZMQ_THREAD_AFFINITY_CPU_REMOVE
    luaX_set_field(L, -1, "ZMQ_THREAD_AFFINITY_CPU_REMOVE", ZMQ_THREAD_AFFINITY_CPU_REMOVE);
#endif
#ifdef ZMQ_THREAD_NAME_PREFIX
    luaX_set_field(L, -1, "ZMQ_THREAD_NAME_PREFIX", ZMQ_THREAD_NAME_PREFIX);
#endif
#ifdef ZMQ_MSG_PROPERTY_ROUTING_ID
    luaX_set_field(L, -1, "ZMQ_MSG_PROPERTY_ROUTING_ID", ZMQ_MSG_PROPERTY_ROUTING_ID);
#endif
#ifdef ZMQ_MSG_PROPERTY_SOCKET_TYPE
    luaX_set_field(L, -1, "ZMQ_MSG_PROPERTY_SOCKET_TYPE", ZMQ_MSG_PROPERTY_SOCKET_TYPE);
#endif
#ifdef ZMQ_MSG_PROPERTY_USER_ID
    luaX_set_field(L, -1, "ZMQ_MSG_PROPERTY_USER_ID", ZMQ_MSG_PROPERTY_USER_ID);
#endif
#ifdef ZMQ_MSG_PROPERTY_PEER_ADDRESS
    luaX_set_field(L, -1, "ZMQ_MSG_PROPERTY_PEER_ADDRESS", ZMQ_MSG_PROPERTY_PEER_ADDRESS);
#endif
#ifdef ZMQ_GSSAPI_NT_HOSTBASED
    luaX_set_field(L, -1, "ZMQ_GSSAPI_NT_HOSTBASED", ZMQ_GSSAPI_NT_HOSTBASED);
#endif
#ifdef ZMQ_GSSAPI_NT_USER_NAME
    luaX_set_field(L, -1, "ZMQ_GSSAPI_NT_USER_NAME", ZMQ_GSSAPI_NT_USER_NAME);
#endif
#ifdef ZMQ_GSSAPI_NT_KRB5_PRINCIPAL
    luaX_set_field(L, -1, "ZMQ_GSSAPI_NT_KRB5_PRINCIPAL", ZMQ_GSSAPI_NT_KRB5_PRINCIPAL);
#endif
  }

  getsockopt_option_enum getsockopt_option(int name) {
    switch (name) {
#ifdef ZMQ_AFFINITY
      case ZMQ_AFFINITY:
        return getsockopt_option_uint64_t;
#endif
#ifdef ZMQ_BACKLOG
      case ZMQ_BACKLOG:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_BINDTODEVICE
      case ZMQ_BINDTODEVICE:
        return getsockopt_option_character_string;
#endif
#ifdef ZMQ_CONNECT_TIMEOUT
      case ZMQ_CONNECT_TIMEOUT:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_CURVE_PUBLICKEY
      case ZMQ_CURVE_PUBLICKEY:
        return getsockopt_option_binary_data_or_Z85_text_string;
#endif
#ifdef ZMQ_CURVE_SECRETKEY
      case ZMQ_CURVE_SECRETKEY:
        return getsockopt_option_binary_data_or_Z85_text_string;
#endif
#ifdef ZMQ_CURVE_SERVERKEY
      case ZMQ_CURVE_SERVERKEY:
        return getsockopt_option_binary_data_or_Z85_text_string;
#endif
#ifdef ZMQ_EVENTS
      case ZMQ_EVENTS:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_FD
      case ZMQ_FD:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_GSSAPI_PLAINTEXT
      case ZMQ_GSSAPI_PLAINTEXT:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_GSSAPI_PRINCIPAL
      case ZMQ_GSSAPI_PRINCIPAL:
        return getsockopt_option_character_string;
#endif
#ifdef ZMQ_GSSAPI_SERVER
      case ZMQ_GSSAPI_SERVER:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL
      case ZMQ_GSSAPI_SERVICE_PRINCIPAL:
        return getsockopt_option_character_string;
#endif
#ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE
      case ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_GSSAPI_PRINCIPAL_NAMETYPE
      case ZMQ_GSSAPI_PRINCIPAL_NAMETYPE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_HANDSHAKE_IVL
      case ZMQ_HANDSHAKE_IVL:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_IMMEDIATE
      case ZMQ_IMMEDIATE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_INVERT_MATCHING
      case ZMQ_INVERT_MATCHING:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_IPV4ONLY
      case ZMQ_IPV4ONLY:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_IPV6
      case ZMQ_IPV6:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_LAST_ENDPOINT
      case ZMQ_LAST_ENDPOINT:
        return getsockopt_option_character_string;
#endif
#ifdef ZMQ_LINGER
      case ZMQ_LINGER:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_MAXMSGSIZE
      case ZMQ_MAXMSGSIZE:
        return getsockopt_option_int64_t;
#endif
#ifdef ZMQ_MECHANISM
      case ZMQ_MECHANISM:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_MULTICAST_HOPS
      case ZMQ_MULTICAST_HOPS:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_MULTICAST_MAXTPDU
      case ZMQ_MULTICAST_MAXTPDU:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_PLAIN_PASSWORD
      case ZMQ_PLAIN_PASSWORD:
        return getsockopt_option_character_string;
#endif
#ifdef ZMQ_PLAIN_SERVER
      case ZMQ_PLAIN_SERVER:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_PLAIN_USERNAME
      case ZMQ_PLAIN_USERNAME:
        return getsockopt_option_character_string;
#endif
#ifdef ZMQ_USE_FD
      case ZMQ_USE_FD:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_RATE
      case ZMQ_RATE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_RCVBUF
      case ZMQ_RCVBUF:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_RCVHWM
      case ZMQ_RCVHWM:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_RCVMORE
      case ZMQ_RCVMORE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_RCVTIMEO
      case ZMQ_RCVTIMEO:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_RECONNECT_IVL
      case ZMQ_RECONNECT_IVL:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_RECONNECT_IVL_MAX
      case ZMQ_RECONNECT_IVL_MAX:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_RECOVERY_IVL
      case ZMQ_RECOVERY_IVL:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_ROUTING_ID
      case ZMQ_ROUTING_ID:
        return getsockopt_option_binary_data;
#endif
#ifdef ZMQ_SNDBUF
      case ZMQ_SNDBUF:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_SNDHWM
      case ZMQ_SNDHWM:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_SNDTIMEO
      case ZMQ_SNDTIMEO:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_SOCKS_PROXY
      case ZMQ_SOCKS_PROXY:
        return getsockopt_option_character_string;
#endif
#ifdef ZMQ_TCP_KEEPALIVE
      case ZMQ_TCP_KEEPALIVE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_TCP_KEEPALIVE_CNT
      case ZMQ_TCP_KEEPALIVE_CNT:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_TCP_KEEPALIVE_IDLE
      case ZMQ_TCP_KEEPALIVE_IDLE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_TCP_KEEPALIVE_INTVL
      case ZMQ_TCP_KEEPALIVE_INTVL:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_TCP_MAXRT
      case ZMQ_TCP_MAXRT:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_THREAD_SAFE
      case ZMQ_THREAD_SAFE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_TOS
      case ZMQ_TOS:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_TYPE
      case ZMQ_TYPE:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_ZAP_DOMAIN
      case ZMQ_ZAP_DOMAIN:
        return getsockopt_option_character_string;
#endif
#ifdef ZMQ_ZAP_ENFORCE_DOMAIN
      case ZMQ_ZAP_ENFORCE_DOMAIN:
        return getsockopt_option_int;
#endif
#ifdef ZMQ_VMCI_BUFFER_SIZE
      case ZMQ_VMCI_BUFFER_SIZE:
        return getsockopt_option_uint64_t;
#endif
#ifdef ZMQ_VMCI_BUFFER_MIN_SIZE
      case ZMQ_VMCI_BUFFER_MIN_SIZE:
        return getsockopt_option_uint64_t;
#endif
#ifdef ZMQ_VMCI_BUFFER_MAX_SIZE
      case ZMQ_VMCI_BUFFER_MAX_SIZE:
        return getsockopt_option_uint64_t;
#endif
#ifdef ZMQ_VMCI_CONNECT_TIMEOUT
      case ZMQ_VMCI_CONNECT_TIMEOUT:
        return getsockopt_option_int;
#endif
      default:
        return getsockopt_option_unknown;
    }
  }

  setsockopt_option_enum setsockopt_option(int name) {
    switch (name) {
#ifdef ZMQ_AFFINITY
      case ZMQ_AFFINITY:
        return setsockopt_option_uint64_t;
#endif
#ifdef ZMQ_BACKLOG
      case ZMQ_BACKLOG:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_BINDTODEVICE
      case ZMQ_BINDTODEVICE:
        return setsockopt_option_character_string;
#endif
#ifdef ZMQ_CONNECT_ROUTING_ID
      case ZMQ_CONNECT_ROUTING_ID:
        return setsockopt_option_binary_data;
#endif
#ifdef ZMQ_CONFLATE
      case ZMQ_CONFLATE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_CONNECT_TIMEOUT
      case ZMQ_CONNECT_TIMEOUT:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_CURVE_PUBLICKEY
      case ZMQ_CURVE_PUBLICKEY:
        return setsockopt_option_binary_data_or_Z85_text_string;
#endif
#ifdef ZMQ_CURVE_SECRETKEY
      case ZMQ_CURVE_SECRETKEY:
        return setsockopt_option_binary_data_or_Z85_text_string;
#endif
#ifdef ZMQ_CURVE_SERVER
      case ZMQ_CURVE_SERVER:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_CURVE_SERVERKEY
      case ZMQ_CURVE_SERVERKEY:
        return setsockopt_option_binary_data_or_Z85_text_string;
#endif
#ifdef ZMQ_GSSAPI_PLAINTEXT
      case ZMQ_GSSAPI_PLAINTEXT:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_GSSAPI_PRINCIPAL
      case ZMQ_GSSAPI_PRINCIPAL:
        return setsockopt_option_character_string;
#endif
#ifdef ZMQ_GSSAPI_SERVER
      case ZMQ_GSSAPI_SERVER:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL
      case ZMQ_GSSAPI_SERVICE_PRINCIPAL:
        return setsockopt_option_character_string;
#endif
#ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE
      case ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_GSSAPI_PRINCIPAL_NAMETYPE
      case ZMQ_GSSAPI_PRINCIPAL_NAMETYPE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_HANDSHAKE_IVL
      case ZMQ_HANDSHAKE_IVL:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_HEARTBEAT_IVL
      case ZMQ_HEARTBEAT_IVL:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_HEARTBEAT_TIMEOUT
      case ZMQ_HEARTBEAT_TIMEOUT:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_HEARTBEAT_TTL
      case ZMQ_HEARTBEAT_TTL:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_IMMEDIATE
      case ZMQ_IMMEDIATE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_INVERT_MATCHING
      case ZMQ_INVERT_MATCHING:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_IPV6
      case ZMQ_IPV6:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_LINGER
      case ZMQ_LINGER:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_MAXMSGSIZE
      case ZMQ_MAXMSGSIZE:
        return setsockopt_option_int64_t;
#endif
#ifdef ZMQ_MULTICAST_HOPS
      case ZMQ_MULTICAST_HOPS:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_MULTICAST_MAXTPDU
      case ZMQ_MULTICAST_MAXTPDU:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_PLAIN_PASSWORD
      case ZMQ_PLAIN_PASSWORD:
        return setsockopt_option_character_string;
#endif
#ifdef ZMQ_PLAIN_SERVER
      case ZMQ_PLAIN_SERVER:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_PLAIN_USERNAME
      case ZMQ_PLAIN_USERNAME:
        return setsockopt_option_character_string;
#endif
#ifdef ZMQ_USE_FD
      case ZMQ_USE_FD:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_PROBE_ROUTER
      case ZMQ_PROBE_ROUTER:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_RATE
      case ZMQ_RATE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_RCVBUF
      case ZMQ_RCVBUF:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_RCVHWM
      case ZMQ_RCVHWM:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_RCVTIMEO
      case ZMQ_RCVTIMEO:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_RECONNECT_IVL
      case ZMQ_RECONNECT_IVL:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_RECONNECT_IVL_MAX
      case ZMQ_RECONNECT_IVL_MAX:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_RECOVERY_IVL
      case ZMQ_RECOVERY_IVL:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_REQ_CORRELATE
      case ZMQ_REQ_CORRELATE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_REQ_RELAXED
      case ZMQ_REQ_RELAXED:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_ROUTER_HANDOVER
      case ZMQ_ROUTER_HANDOVER:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_ROUTER_MANDATORY
      case ZMQ_ROUTER_MANDATORY:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_ROUTER_RAW
      case ZMQ_ROUTER_RAW:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_ROUTING_ID
      case ZMQ_ROUTING_ID:
        return setsockopt_option_binary_data;
#endif
#ifdef ZMQ_SNDBUF
      case ZMQ_SNDBUF:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_SNDHWM
      case ZMQ_SNDHWM:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_SNDTIMEO
      case ZMQ_SNDTIMEO:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_SOCKS_PROXY
      case ZMQ_SOCKS_PROXY:
        return setsockopt_option_character_string;
#endif
#ifdef ZMQ_STREAM_NOTIFY
      case ZMQ_STREAM_NOTIFY:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_SUBSCRIBE
      case ZMQ_SUBSCRIBE:
        return setsockopt_option_binary_data;
#endif
#ifdef ZMQ_TCP_KEEPALIVE
      case ZMQ_TCP_KEEPALIVE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_TCP_KEEPALIVE_CNT
      case ZMQ_TCP_KEEPALIVE_CNT:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_TCP_KEEPALIVE_IDLE
      case ZMQ_TCP_KEEPALIVE_IDLE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_TCP_KEEPALIVE_INTVL
      case ZMQ_TCP_KEEPALIVE_INTVL:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_TCP_MAXRT
      case ZMQ_TCP_MAXRT:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_TOS
      case ZMQ_TOS:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_UNSUBSCRIBE
      case ZMQ_UNSUBSCRIBE:
        return setsockopt_option_binary_data;
#endif
#ifdef ZMQ_XPUB_VERBOSE
      case ZMQ_XPUB_VERBOSE:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_XPUB_VERBOSER
      case ZMQ_XPUB_VERBOSER:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_XPUB_MANUAL
      case ZMQ_XPUB_MANUAL:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_XPUB_NODROP
      case ZMQ_XPUB_NODROP:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_XPUB_WELCOME_MSG
      case ZMQ_XPUB_WELCOME_MSG:
        return setsockopt_option_binary_data;
#endif
#ifdef ZMQ_ZAP_DOMAIN
      case ZMQ_ZAP_DOMAIN:
        return setsockopt_option_character_string;
#endif
#ifdef ZMQ_ZAP_ENFORCE_DOMAIN
      case ZMQ_ZAP_ENFORCE_DOMAIN:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_TCP_ACCEPT_FILTER
      case ZMQ_TCP_ACCEPT_FILTER:
        return setsockopt_option_binary_data;
#endif
#ifdef ZMQ_IPC_FILTER_GID
      case ZMQ_IPC_FILTER_GID:
        return setsockopt_option_gid_t;
#endif
#ifdef ZMQ_IPC_FILTER_PID
      case ZMQ_IPC_FILTER_PID:
        return setsockopt_option_pid_t;
#endif
#ifdef ZMQ_IPC_FILTER_UID
      case ZMQ_IPC_FILTER_UID:
        return setsockopt_option_uid_t;
#endif
#ifdef ZMQ_IPV4ONLY
      case ZMQ_IPV4ONLY:
        return setsockopt_option_int;
#endif
#ifdef ZMQ_VMCI_BUFFER_SIZE
      case ZMQ_VMCI_BUFFER_SIZE:
        return setsockopt_option_uint64_t;
#endif
#ifdef ZMQ_VMCI_BUFFER_MIN_SIZE
      case ZMQ_VMCI_BUFFER_MIN_SIZE:
        return setsockopt_option_uint64_t;
#endif
#ifdef ZMQ_VMCI_BUFFER_MAX_SIZE
      case ZMQ_VMCI_BUFFER_MAX_SIZE:
        return setsockopt_option_uint64_t;
#endif
#ifdef ZMQ_VMCI_CONNECT_TIMEOUT
      case ZMQ_VMCI_CONNECT_TIMEOUT:
        return setsockopt_option_int;
#endif
      default:
        return setsockopt_option_unknown;
    }
  }
}

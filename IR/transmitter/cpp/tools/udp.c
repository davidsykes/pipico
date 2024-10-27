
  // Make a pcb
  struct udp_pcb *mPcb = nullptr;

#if NO_SYS == 1
  cyw43_arch_lwip_begin();
#endif
  err_t _bindErr = ERR_OK;

  if ((mPcb = udp_new_ip_type(IPADDR_TYPE_V4)) != NULL) {
    // Set receive callback
    udp_recv(
        mPcb,
        [](void *arg, udp_pcb *pcb, pbuf *p, const ip_addr_t *addr,
           u16_t port) {
          // Get ip of incoming packet
          const auto ip = ipaddr_ntoa(addr);

          // Get the length of the packet
          const auto len = p->len;

          // Get the payload of the packet
          const auto payload = p->payload;

          // Print
          printf("Received packet from %s:%d with length %d\n", ip, port, len);

          // Free pbuffer
          pbuf_free(p);
        },
        NULL);

    _bindErr = udp_bind(mPcb, IP_ADDR_ANY, serverPort);
  } else
    _bindErr = ERR_MEM;
#if NO_SYS == 1
  cyw43_arch_lwip_end();
#endif

  // Bind the pcb to the port
  // const auto result = udp_bind(mPcb, IP_ADDR_ANY, port);

  if (_bindErr != ERR_OK) {
    printf("Failed to bind server to UDP pcb! error=%d\n", _bindErr);
  } else {
    printf("Bound server to UDP pcb to port %d\n", port);
  }

  // Connect
  const auto connError = udp_connect(mPcb, IP_ADDR_ANY, port);

  if (connError != ERR_OK) {
    printf("Failed to connect UDP pcb! error=%d\n", connError);
  } else {
    printf("Connected UDP pcb to port %d\n", port);
  };

  while (true) {

    if (connected) {
      watchdog_update();

    } else {
      printf("not connected :((((()))))\n");
    }

#if PICO_CYW43_ARCH_POLL
    // if you are using pico_cyw43_arch_poll, then you must poll periodically
    // from your main loop (not from a timer) to check for Wi-Fi driver or lwIP
    // work that needs to be done.
    cyw43_arch_poll();
    sleep_ms(BEACON_INTERVAL_MS);
#else
    // if you are not using pico_cyw43_arch_poll, then WiFI driver and lwIP work
    // is done via interrupt in the background. This sleep is just an example of
    // some (blocking) work you might be doing.
    sleep_ms(BEACON_INTERVAL_MS);
#endif
  }

  return 0;


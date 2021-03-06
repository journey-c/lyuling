#include "front.h"
#include "net/tcp.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void *front_listen(void *arg) {
  char err[256];
  tcp_listener *l = net_tcp_listen(err, "0.0.0.0", 8360, 5);
  if (!l) {
    printf("[front_listen] listen error: %s\n", err);
    exit(-1);
  }
  printf("[front_listen] listen 8360\n");

  for (;;) {
    tcp_conn *conn = net_tcp_accept(err, l);
    if (!conn) {
      printf("[front_listen] accept error: %s\n", err);
      break;
    }
    printf("new conn: %d\n", conn->fd);
  }
  return NULL;
}

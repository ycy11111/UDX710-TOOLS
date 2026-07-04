#include "mongoose.h"
#include <stdio.h>
#include <signal.h>

static volatile int s_running = 1;

static void signal_handler(int sig) {
  (void)sig;
  s_running = 0;
}

static void fn(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *)ev_data;
    mg_http_reply(c, 200, "", "OK\n");
  }
}

int main() {
  struct mg_mgr mgr;
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);
  mg_mgr_init(&mgr);
  mg_http_listen(&mgr, "http://0.0.0.0:6688", fn, NULL);
  fprintf(stderr, "Server started on :6688\n");
  while (s_running) {
    mg_mgr_poll(&mgr, 100);
  }
  mg_mgr_free(&mgr);
  fprintf(stderr, "Server stopped\n");
  return 0;
}

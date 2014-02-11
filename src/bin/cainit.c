#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <uv.h>
#include "common.h"

#define PORT 420

// Macro to check exit status of functions that return such.
#define CHECK(status, msg) \
if (status != 0) { \
fprintf(stderr, "%s: %s\n", msg, uv_err_name(status)); \
exit(1); \
}

// Max number of write handles for libuv to maintain.
#define MAX_WRITE_HANDLES 10

typedef enum { false , true } bool;

static int request_num = 1;
static uv_loop_t* uv_loop;
static uv_tcp_t server;


// Add Amin processor to struct.
typedef struct {
  uv_tcp_t handle;
  uv_write_t write_req;
  int request_num;
} client_t;

void on_close(uv_handle_t* handle) {
  client_t* client = (client_t*) handle->data;
  LOGF("[ %5d ] connection closed\n\n", client->request_num);
  free(client);
}

void alloc_cb(uv_handle_t * handle, size_t suggested_size, uv_buf_t* buf) {
    *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t * buf) {
  ssize_t parsed;
  LOGF("on read: %ld",nread);
  client_t* client = (client_t*) tcp->data;
  if (nread >= 0) {
    parsed = 0;
    if (parsed < nread) {
      LOG("parse error");
      uv_close((uv_handle_t*) &client->handle, on_close);
    }
  } else {
    if (nread != UV_EOF) {
      UVERR(nread, "read");
    }
    uv_close((uv_handle_t*) &client->handle, on_close);
  }
  free(buf->base);
}


void on_connect(uv_stream_t* server_handle, int status) {
  CHECK(status, "connect");

  client_t* client = (client_t*)malloc(sizeof(client_t));
  client->request_num = request_num;
  request_num++;

  LOGF("[ %5d ] new connection", request_num);

  uv_tcp_init(uv_loop, &client->handle);

    // In here in haywire / simple http examples they setup a HTTP parser, will look into async call here using libuv to amin library to do such 
  // that way we can hook the same point in amin client > go through the machine/filter/command stack as current in perl.

  int r = uv_accept(server_handle, (uv_stream_t*)&client->handle);
  CHECK(r, "accept");

  uv_read_start((uv_stream_t*)&client->handle, alloc_cb, on_read);
}

void initialiseAinit()
{
  bool haveConfig;
  LOG("initialiseAinit Called");
  
  // Check for config ( this would essentially be an adminlist with either external uri or a init profile contained within ) 
  
  if ( haveConfig ) 
  {
    // load uri -> pass to amin library
  } else {
    // here we could scan for systemd / upstart and gracefully fallback to such if they exist.
    // could also be a config param to support redhat/ubuntu etc profiles.
  }
}

void setupSocket()
{
   uv_loop = uv_default_loop();
  int r = uv_tcp_init(uv_loop, &server);
  CHECK(r, "tcp_init");
  r = uv_tcp_keepalive(&server,1,60);
  CHECK(r, "tcp_keepalive");
  struct sockaddr_in address;
  r = uv_ip4_addr("0.0.0.0", PORT, &address);
  CHECK(r, "ip4_addr");
  r = uv_tcp_bind(&server, (const struct sockaddr*)&address, 0);
  CHECK(r, "tcp_bind");
  uv_listen((uv_stream_t*)&server, MAX_WRITE_HANDLES, on_connect);
  LOG("Ainit daemon listening");
  uv_run(uv_loop,UV_RUN_DEFAULT);
}

int main(int argc, char* argv[])
{
  int pid = getpid();
  LOG("Welcome to Ainit version 0.0.0.1\n");
  LOG("Today brought to you by caffiene and MoonAlice(tm)...\n");
  LOGF("We currently have balmy conditions, 70, sunny and PID [ %5d ] \n", pid);
  
  
  // Initialise Ainit
  initialiseAinit();
  
  // Initialise socket, we ALWAYS do such regardless of init executed, this allows us to recieve amin profiles even when falling back to 
  // upstart / systemd 
  setupSocket();
  
  
  // TODO Setup handler to cleanup on kernel termination. 
  while (1)
  {

  }
  return (0);
}
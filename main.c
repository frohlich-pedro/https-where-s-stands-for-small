#include <myio.h>
#include <mysocks.h>

int main() {
  int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP), c, f, n;
  char b[1024 * 1024], h[1024 * 1024];
  struct sockaddr_in a = {.sin_family = AF_INET, .sin_port = htons(8080), .sin_addr.s_addr = htonl(INADDR_ANY)};
  bind(s, (struct sockaddr*)&a, sizeof(a));
  listen(s, 1);
l:c = accept(s, 0, 0);
  recv(c, b, 1024 * 1024 - 1, 0);
  f = open("index.html", 0);
  n = read(f, h, 1024 * 1024 - 1);
  close(f);
  h[n] = 0;
  send(c, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", 100, 0);
  send(c, h, n, 0);
  close(c);
  goto l;
}

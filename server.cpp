#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>

#include <unistd.h>

#include "common.h"

inline void usage(const char* prog)
{
  using namespace std;
  cerr << "usage % " << prog << "[-p port]" << '\n';
}

int main(int argc, char** argv)
{
  using namespace std;

#if 0
  int port = 12345;
#else
  int port = 200;
#endif  
  for (int opt; (opt = getopt(argc, argv, "p:")) != -1 ; ) {
    switch (opt) {
    case 'p': port = atoi(optarg); break;
    default: usage(argv[0]);       return 1;
    }
  }

  int desc = socket(AF_INET, SOCK_STREAM, 0);
  if (desc < 0) {
    cerr << "socket failed" << '\n';
    return err_info();
  }

  struct sweeper {
    int desc;
    sweeper(int d) : desc {d} {}
    ~sweeper() { close(desc); }
  } sweeper {desc};
#if 1
  sockaddr_in addr = {AF_INET, (in_port_t)port, { INADDR_ANY } };
#else
  sockaddr_in addr = {AF_INET, htons(port), { htonl(INADDR_ANY) } };
#endif  
  if (bind(desc, (sockaddr*)&addr, sizeof addr) < 0) {
    cerr << "bind failed" << '\n';
    return err_info();
  }
  
  if (listen(desc, 1) < 0) {
    cerr << "listen failed" << '\n';
    return err_info();
  }

  sockaddr tmp;
  socklen_t len = sizeof tmp;
  int fd = accept(desc, &tmp, &len);
  if (fd < 0) {
    cerr << "accept failed" << '\n';
    return err_info();
  }

  struct sweeper2 {
    int fd;
    sweeper2(int f) : fd {f} {}
    ~sweeper2() { close(fd); }
  } sweeper2 {fd};

  char buffer[256];
  int n = read(fd, &buffer, sizeof buffer);
  if (n < 0) {
    cerr << "read failed" << '\n';
    return err_info();
  }
  if (buffer[n-1] != '\0') {
    cerr << "not terminated" << '\n';
    buffer[n-1] = '\0';
  }
  cout << buffer << '\n';

  string msg = "howdy";
  if (write(fd, &msg[0], msg.length()+1) < 0) {
    cerr << "write failed" << '\n';
    return err_info();
  }

  return 0;
}

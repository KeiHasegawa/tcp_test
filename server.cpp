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

  int port = 128;
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

  sockaddr_in addr = {AF_INET, (in_port_t)port, { INADDR_ANY } };
  if (bind(desc, (sockaddr*)&addr, sizeof addr) < 0) {
    cerr << "bind failed" << '\n';
    return err_info();
  }
  
  if (listen(desc, SOMAXCONN) < 0) {
    cerr << "listen failed" << '\n';
    return err_info();
  }

  sockaddr tmp;
  socklen_t len;
  if (accept(desc, &tmp, &len) < 0) {
    cerr << "accept failed" << '\n';
    return err_info();
  }

  cout << "accept sucessed" << '\n';

#if 0
  string msg = "howdy";
  if (write(desc, &msg[0], msg.length()+1) < 0) {
    cerr << "write failed" << '\n';
    return 1;
  }
#endif
  return 0;
}

void debug(int desc)
{
  using namespace std;
  char buffer[256];
  int n = read(desc, &buffer, sizeof buffer);
  if (n < 0) {
    cerr << "read failed" << '\n';
    return (void)err_info();
  }
  cout << buffer << '\n';
}


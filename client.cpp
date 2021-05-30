#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "common.h"

inline void usage(const char* prog)
{
  using namespace std;
  cerr << "usage % " << prog << "[-p port][-h host][-m msg]" << '\n';
}

int main(int argc, char** argv)
{
  using namespace std;

  int port = 200;
  string host = "localhost";
  string msg = "hello world";
  for (int opt; (opt = getopt(argc, argv, "p:h:m:")) != -1 ; ) {
    switch (opt) {
    case 'p': port = atoi(optarg); break;
    case 'h': host = optarg;       break;
    case 'm': msg = optarg;        break;
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

  hostent* ent = gethostbyname(host.c_str());
  if (!ent) {
    cerr << "gethostbyname failed" << '\n';
    return 1;
  }
  auto in = *(in_addr_t*)*ent->h_addr_list;
#if 1
  sockaddr_in addr = { AF_INET, (in_port_t)port, { in } };
#else
  sockaddr_in addr = { AF_INET, htons(port), { htonl(in) } };
#endif
  if (connect(desc, (sockaddr*)&addr, sizeof addr) < 0) {
    cerr <<"connect failed" << '\n';
    return 1;
  }

  if (write(desc, &msg[0], msg.length()+1) < 0) {
    cerr << "write failed" << '\n';
    return 1;
  }

  char buffer[256];
  int n = read(desc, &buffer[0], sizeof buffer);
  if (n < 0) {
    cerr << "read failed" << '\n';
    return 1;
  }

  cout << "n = " << dec << n << '\n';
  cout.fill('0');
  for (int i = 0 ; i != n ;++i )
    cout << ' ' << hex << setw(2) << int(buffer[i]);
  cout << '\n';
 
  return 0;
}

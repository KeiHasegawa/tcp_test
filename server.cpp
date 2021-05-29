#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>

#include <unistd.h>

inline void usage(const char* prog)
{
  using namespace std;
  cerr << "usage % " << prog << "[-p port]" << '\n';
}

int main(int argc, char** argv)
{
  using namespace std;

  int port = 257;
  for (int opt; (opt = getopt(argc, argv, "p:")) != -1 ; ) {
    switch (opt) {
    case 'p': port = atoi(optarg); break;
    default: usage(argv[0]);       return 1;
    }
  }

  int soc = socket(AF_INET, SOCK_STREAM, 0);
  if (soc < 0) {
    cerr << "socket failed" << '\n';
    return 1;
  }

  sockaddr_in addr = {AF_INET, htons(port), { INADDR_ANY } };
  if (bind(soc, (sockaddr*)&addr, sizeof addr) < 0) {
    cerr << "bind failed" << '\n';
    return 1;
  }
  
  if (listen(soc, SOMAXCONN) < 0) {
    cerr << "listen failed" << '\n';
    return 1;
  }
  return 0;
}

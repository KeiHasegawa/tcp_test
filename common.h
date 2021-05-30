#ifndef COMMON_H
#define COMMON_H

inline int err_info()
{
  using namespace std;
  switch (errno) {
  case EADDRINUSE: cerr << "EADDRINUSE" << '\n'; break;
  case EADDRNOTAVAIL: cerr << "EADDRNOTAVAIL" << '\n'; break;
  case EAFNOSUPPORT: cerr << "EAFNOSUPPORT" << '\n'; break;
  case EBADF: cerr << "EBADF" << '\n'; break;
  case EINVAL: cerr << "EINVAL" << '\n'; break;
  case ENOTSOCK: cerr << "ENOTSOCK" << '\n'; break;
  case EOPNOTSUPP: cerr << "EOPNOTSUPP" << '\n'; break;
  case EACCES: cerr << "EACCES" << '\n'; break;
  case EDESTADDRREQ: cerr << "EDESTADDRREQ" << '\n'; break;
  case EISDIR:  cerr << "EISDIR" << '\n'; break;
  case EIO: cerr << "EIO" << '\n'; break;
  case ELOOP: cerr << "ELOOP" << '\n'; break;
  case ENAMETOOLONG: cerr << "ENAMETOOLONG" << '\n'; break;
  case ENOENT: cerr << "ENOENT" << '\n'; break;
  case ENOTDIR: cerr << "ENOTDIR" << '\n'; break;
  case EROFS: cerr << "EROFS" << '\n'; break;
  case EISCONN: cerr << "EISCONN" << '\n'; break;
  case ENOBUFS: cerr << "ENOBUFS" << '\n'; break;
  case EAGAIN: cerr << "EAGAIN" << '\n'; break; 
  case ECONNRESET: cerr << "ECONNRESET" << '\n'; break; 
  case EINTR: cerr << "EINTR" << '\n'; break; 
  case ENOTCONN: cerr << "ENOTCONN" << '\n'; break; 
  case ETIMEDOUT: cerr << "ETIMEDOUT" << '\n'; break; 
  case ENOMEM: cerr << "ENOMEM" << '\n'; break; 
  default: cerr << "unknown error" << '\n'; break;
  }
  return 1;
}

#endif // COMMON_H

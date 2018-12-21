#include <iostream>
#include "Multicast.hpp"

int main(int argc, char const *argv[])
{
	char msg[] = "Testando a execução";
	char ip[] = "224.0.0.1"; 
  Multicast m(ip, 65534);
  m.sendMessage(msg);
  /* code */
  return 0;
}

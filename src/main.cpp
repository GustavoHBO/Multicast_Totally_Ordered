#include <iostream>
#include "./include/Multicast.hpp"

int main(int argc, char const *argv[])
{
  Multicast m("224.0.0.1", 65534);
  m.sendMessage("Testando a execução");
  /* code */
  return 0;
}

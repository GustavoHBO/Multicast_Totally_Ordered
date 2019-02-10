#include <iostream>
#include "Teste.hpp"

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    char arg = argv[1][0];
    if (arg == '1')
    {
      Teste t;
      t.teste_00();
    }
    else if (arg == '2')
    {
      Teste t;
      t.teste_01();
    }
    else if (arg == '3')
    {
      Teste t;
      t.teste_04(argc, argv);
    }
    else if (arg == '4')
    {
      Teste t;
      t.teste_05();
    }
    else if (arg == '5')
    {
      Teste t;
      t.teste_06();
    }
  }
  return 1;
}

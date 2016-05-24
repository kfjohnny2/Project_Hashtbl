# Hash Table
Implementação de uma tabela de dispersão genérica usando uma aplicação simples para um banco

## Variações
Seguem os 3 tipos de implementação de acordo com o solicitado no documento do trabalho

#### Versão 1
Uma chave composta por um inteiro correspondente ao número da conta corrente.
```cpp
using AcctKey = int;
```

#### Versão 2
Uma chave composta de dois campos definidos por um std::pair , que contém o nome do cliente e o número da conta.
```cpp
using AcctKey = std::pair<std::string, int>;
```

#### Versão 3
Uma chave composta por meio de 4 campos definidos por uma std::tuple, que contém o nome do cliente, o código do banco, o número da agência e o número da conta.
```cpp
using AcctKey = std::tuple<std::string, int, int, int>;
```

## Como compilar
No terminal, dentro da pasta do projeto digite :

### Para a Versão 1

```shell
g++ -std=c++11 -Wall -I include/ src/pgm_ht.cpp -o bin/hash -D SIMPLE
```

### Para a Versão 2

```shell
g++ -std=c++11 -Wall -I include/ src/pgm_ht.cpp -o bin/hash -D STILLSIMPLE
```

### Para a Versão 3

```shell
g++ -std=c++11 -Wall -I include/ src/pgm_ht.cpp -o bin/hash -D NOTTHATSIMPLE
```
Executar:
```shell
./bin/hash
```

## Autor
Johnnylee Bryan Marques da Rocha
 - [GitHub](https://github.com/kfjohnny2)

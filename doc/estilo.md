# Diretrizes de estilo (WIP)
É importante que as pessoas que programam num único projeto se organizem para usar o mesmo estilo, para que o código se mantenha organizado e fácil de ler.

#### Índice:
* [Acentos](#acentos)
* [Indentação e posição das chaves](#indentação-e-posição-das-chaves)
  + [Exceção](#exceção)
* [Tamanho máximo da linha](#tamanho-máximo-da-linha)
  + [Como e onde dividir linhas grandes](#como-e-onde-dividir-linhas-grandes)
    - [Strings](#strings)
* [Whitespace](#whitespace)
* [Comentários](#comentários)
* [Identificadores e nomes](#identificadores-e-nomes)
  + [Funções e tipos](#funções-e-tipos)
  + [Variáveis não constantes](#variáveis-não-constantes)
  + [Variáveis constantes e `#define`s](#variáveis-constantes-e-defines)
  + [Valores de `enum`](#valores-de-enum)
  + [Nomes de arquivo `.c` e `.h`](#nomes-de-arquivo-c-e-h)

<small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc</a></i></small>


-------------
**TO-DO:**
- Comentários de documentação, com exemplos de uso pelo CB
- Comentários separadores de seções
-------------

<!--%%%%%%%%%%%%%%%%%%%%%%%%%%%-->

## Acentos
Não coloque letras com acentos no código fonte. O GitHub Desktop tem um bug que faz com que commits que incluem apenas algumas das mudanças de um arquivo possam falhar se o arquivo contiver letras com acentos.

Para evitar ambiguidades no texto em português:
- Ao invés de escrever a palavra `é`, escrever `eh`
- Ao invés de escrever a letra `à` (craseado), escrever `ah`. Mesmo se essa letra fizer parte de uma palavra com outras letras (ex: `às -> ahs`, `àquele -> ahquele`).

<!--%%%%%%%%%%%%%%%%%%%%%%%%%%%-->

## Indentação e posição das chaves
Sempre utilize indentação correta. As chaves de abertura devem estar sozinhas na linha, assim como as chaves de fechamento:
```c
//======================================
// ✔️ Certo:
//======================================
if (x > 0)
{
    printf("x eh positivo\n");
}
else
{
    printf("x nao eh positivo\n");
}

//======================================
// ❌ Errado:
//======================================
if (x > 0) {
    printf("x eh positivo\n");
} else {
    printf("x nao eh positivo\n");
}

//======================================
// ❌ Errado:
//======================================
if (x > 0) {
    printf("x eh positivo\n");
}
else {
    printf("x nao eh positivo\n");
}

//======================================
// ❌ Errado:
//======================================
if (x > 0)
{
printf("x eh positivo\n");
}
else
{
printf("x nao eh positivo\n");
}

//======================================
// ❌ Errado:
//======================================
if (x > 0)
    {
    printf("x eh positivo\n");
    }
else
    {
    printf("x nao eh positivo\n");
    }
```

### Exceção
Uma exceção é que blocos podem estar inteiramente em uma linha só:
```c
// ✔️ OK
if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {   posFutura.x -= 1; }
```
Mas cuidado para não ultrapassar o tamanho máximo da linha.

<!--%%%%%%%%%%%%%%%%%%%%%%%%%%%-->

## Tamanho máximo da linha
80 caracteres. Assim fica possível deixar 2 arquivos de código abertos ao mesmo tempo, lado a lado:

![]("Imagem não adicionada ainda")

Note que esta é uma tela 1600x900. Numa Full HD (1920x1080) ficaria mais espaçosa (talvez caibam até 3), e em uma 1366x768 (comum em notebooks) isso provavelmente é inviável.

### Como e onde dividir linhas grandes
TODO

#### Strings
TODO

<!--%%%%%%%%%%%%%%%%%%%%%%%%%%%-->

## Whitespace
TODO

<!--%%%%%%%%%%%%%%%%%%%%%%%%%%%-->

## Comentários
TODO

<!--%%%%%%%%%%%%%%%%%%%%%%%%%%%-->

## Identificadores e nomes
Todos os identificadores e nomes devem ser descritivos, deixando o mais claro possível o propósito da coisa sendo nomeada.

### Funções e tipos
As iniciais das palavras devem ser maiúsculas, e o resto das letras devem ser minúsculas. Não deve ter nenhum separador entre as palavras:

Exemplos:
```c
void MoverJog(GameState* gs);
```
```c
static void DesenharJogador(GameState* gs, Texture2D* spriteJog);
```
```c
// Tipos de tile
typedef enum {
    /* ... */
}
Tile;
```
A função `main` é uma exceção.

### Variáveis não constantes
Iniciais de palavra maiúsculas, exceto na primeira palavra. O resto das letras devem ser minúsculas. Sem separador.

Exemplos:
```c
TODO: exemplos
```

### Variáveis constantes e `#define`s
Todas as letras devem estar maiúsculas, e as palavras separadas por `_`.

Exemplos:
```c
// Velocidade do jogador (por segundo)
#define VEL_JOG 150.0f
```
```c
TODO: exemplo de variável constante
```

### Valores de `enum`
Mesma regra que variáveis constantes, ou então esta regra:
> Mesma regra que tipos, mas com um prefixo em maiúsculas. O prefixo deve ser igual para todos os valores de um mesmo enumerador. O prefixo deve ser separado do resto do nome por um `_`.

Exemplo:
```c
// Tipos de tile
typedef enum {
    // Indefinido (Nao contem nada, nem mesmo chao)
    TILE_vazio = 0,
    // Mostra grafico de chao e nao colide
    TILE_chao,
    // Mostra grafico de parede e colide
    TILE_parede,
    // Mostra grafico de chao e colide
    TILE_paredeInvisivel
}
Tile;
```

### Nomes de arquivo `.c` e `.h`
Todas as letras minúsculas, e palavras separadas por `_`.

Exemplos:
```c
TODO: exemplos
```




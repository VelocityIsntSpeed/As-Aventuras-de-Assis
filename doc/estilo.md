# Diretrizes de estilo
É importante que utilizemos um estilo consistente, para maior produtividade.

-------------
**TO-DO:**
- Strings de documentação, com exemplos de uso pelo CB
- Comentários separadores
-------------

<!--%%%%%%%%%%%%%%%%%%%%%%%%%%%-->

## Acentos
Não coloque letras com acentos no código fonte. O GitHub Desktop tem um bug que faz com que commits que incluem apenas algumas mudanças de um arquivo possam falhar se o arquivo contiver letras com acentos.

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
```TODO: exemplos```

### Variáveis não constantes
Iniciais de palavra maiúsculas, exceto na primeira palavra. O resto das letras devem ser minúsculas. Sem separador.  
```TODO: exemplos```

### Variáveis constantes e `#define`s
Todas as letras devem estar maiúsculas, e as palavras separadas por `_`.

Exemplo:
```c
// Velocidade do jogador (por segundo)
#define VEL_JOG 150.0f
```

### Valores de `enum`
Mesma regra que variáveis constantes, ou então esta regra:
> Mesma regra que tipos, mas com um prefixo em maiúsculas. O prefixo deve ser igual para todos os valores de um mesmo enumerador. O prefixo deve ser separado do resto do nome por um `_`.  
```TODO: exemplo```

### Nomes de arquivo `.c` e `.h`
Todas as letras minúsculas, e palavras separadas por `_`.  
```TODO: exemplos```




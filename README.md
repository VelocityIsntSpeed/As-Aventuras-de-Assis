# Grupo42-IntProg1
Este é o repositório GitHub para o desenvolvimento do jogo do Grupo 42. Usaremos a biblioteca SDL (Simple Directmedia Layer) e o Visual Studio 2017 ou 2019 (não foi decidido qual ainda).

## Instruções para configurar o ambiente de desenvolvimento:
É preciso instalar o VS e o SDL.

### Instalando o Visual Studio 2017
Baixar diretamente da Microsoft não é recomendado.
O Instalador do VS17 pode ser encontrado aqui:
https://www.techspot.com/downloads/6278-visual-studio.html

Baixe a versão `Free Community Edition` no lado esquerdo da página. O instalador tem a assinatura digital da Microsoft, e portanto é confiável.

Nas opções de instalação, selecione
![](https://www.wikihow.com/images/thumb/2/23/Set-Up-SDL-with-Visual-Studio-2017-Step-3-Version-2.jpg/aid9342314-v4-900px-Set-Up-SDL-with-Visual-Studio-2017-Step-3-Version-2.jpg)





### Instalado o Visual Studio 2019


### Instalando o SDL
Baixe o SDL aqui:
https://www.libsdl.org/download-2.0.php

Na seção entitulada "Development Libraries:" baixe o aqrquivo `SDL2-devel-2.0.9-VC.zip`.

Descompacte-o e coloque-o numa pasta `C:\SDL\` do seu computador, e renomeie-o para SDL2. A árvore de diretórios deverá ficar assim:
```
C:\
  SDL\
    SDL2\
      docs\
      include\
      lib\
      [e vários arquivos de texto]
```

Com isso, sua instalação do SDL já está completa, e o projeto do Visual Studio deverá funcionar sem configurar nada.

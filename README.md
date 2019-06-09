# Grupo42-IntProg1
Este é o repositório GitHub para o desenvolvimento do jogo do Grupo 42 para o projeto da disciplina Introdução à Programação. Usaremos a biblioteca SDL (Simple Directmedia Layer) e o Visual Studio 2017 ou 2019 (não foi decidido qual ainda). A pasta `Jogo42` é um projeto do VS17, já configurado para funcionar com um SDL instalado da maneira descrita aqui.

## Instruções para configurar o ambiente de desenvolvimento:
É preciso instalar o VS e o SDL. As instruções aqui são apenas para Windows.

### Instalando o Visual Studio 2017
Baixar diretamente da Microsoft não é recomendado.
O Instalador do VS17 pode ser encontrado aqui:
https://www.techspot.com/downloads/6278-visual-studio.html

Baixe a versão `Free Community Edition` do botão no lado esquerdo da página. O instalador tem a assinatura digital da Microsoft, portanto é confiável.

Nas opções de instalação, selecione `Desktop development with C++` (`Desenvolvimento para desktop com C++` em português):
![](https://www.wikihow.com/images/thumb/2/23/Set-Up-SDL-with-Visual-Studio-2017-Step-3-Version-2.jpg/aid9342314-v4-900px-Set-Up-SDL-with-Visual-Studio-2017-Step-3-Version-2.jpg)

O instalador irá baixar os arquivos necessários, que será em torno de 6-7 GB.

Se você quiser, também pode instalar os pacotes de idiomas que quiser na aba `Language Packs` (`Pacotes de Idiomas`).

### Instalado o Visual Studio 2019
Eu (Leandro Gabriel) não instalei o Visual Studio 2019, então não posso dar instruções de instalação detalhadas. Mas as instruções acima devem servir. Provavelmente é melhor baixar o VS19 do site oficial da Microsoft.

### Instalando o SDL
Baixe o SDL aqui:
https://www.libsdl.org/download-2.0.php

Na seção entitulada "Development Libraries:", baixe o aqrquivo `SDL2-devel-2.0.9-VC.zip`.

Descompacte-o e coloque-o numa pasta `C:\SDL\` do seu computador, e renomeie-o para SDL2. Deverão existir esses diretórios:
```
C:\
  SDL\
    SDL2\
      docs\
      include\
      lib\
      [e vários arquivos de texto]
```

Com isso, sua instalação do SDL já está completa, e o projeto do VS17 desse repositório deverá funcionar sem configurar nada.
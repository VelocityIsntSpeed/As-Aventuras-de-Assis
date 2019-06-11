# Grupo42-IntProg1
Este é o repositório GitHub para o desenvolvimento do jogo do Grupo 42 para o projeto da disciplina Introdução à Programação. Usaremos a biblioteca SDL (Simple Directmedia Layer) e o Visual Studio 2017 ou 2019 ou Code::Blocks (nâo foi decidido qual ainda).

A pasta `Jogo42_CB` é um projeto de CodeBlocks, e para usá-lo é necessário apenas ter o SDL versão MinGW num diretório específico (veja instruções abaixo).

A pasta `Jogo42_VS` é um projeto de Visual Studio 2017, e para usá-lo é necessário configurar os diretórios de busca do compilador e linker, além de ter o SDL versão Visual C++.

## Instruções para configurar o ambiente de desenvolvimento:
É preciso instalar a IDE (VS ou CB) e o SDL. As instruções aqui são apenas para Windows.

### Instalando o Code::Blocks
http://www.codeblocks.org/downloads/26
Baixe e use o instalador `codeblocks-17.12mingw-setup.exe`.

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

### Instalando o SDL para Code::Blocks
https://www.libsdl.org/download-2.0.php
Baixe o arquivo `SDL2-devel-2.0.9-mingw.tar.gz`.

Dentro desse arquivo compacatado há a pasta `SDL2-2.0.9` (Pode ser necessário descompactá-lo duas vezes). Coloque essa pasta `SDL2-2.0.9` em `C:\Users\Public\` (ficará `C:\Users\Public\SDL2-2.0.9\`).

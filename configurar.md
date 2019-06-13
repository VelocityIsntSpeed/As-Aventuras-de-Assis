# Instruções para configurar o ambiente de desenvolvimento
Instruções para instalar/configurar no Windows as ferramentas e bibliotecas necessárias:

* Windows Explorer
* Code::Blocks
* Raylib
* SDL

<!-- TODO: adicionar instruções para VS e SDL para Visual C++ -->
<!-- TODO: adionionar links à lista acima para as respectivas seções -->


## Configurar Windows Explorer
Por padrão, o Explorer não mostra extensões de arquivos com extensão conhecida, nem mostra arquivos ocultos.

![](config-explorer.png)

Em qualquer janela do explorer, acesse:
1. Aba `exibir`
2. `Mostrar/ocultar`
3. Marque `Extensões de nomes de arquivos` e `Itens ocultos`


## Instalar o Code::Blocks
http://www.codeblocks.org/downloads/26  
Baixe e execute o instalador `codeblocks-17.12mingw-setup.exe`.


## Instalar o Raylib
https://raysan5.itch.io/raylib  
Baixe e execute o instalador `raylib 2.5 Windows Installer (with MinGW compiler)`.


## Instalar o SDL
https://www.libsdl.org/download-2.0.php  
Baixe o arquivo `SDL2-devel-2.0.9-mingw.tar.gz`.

Dentro desse arquivo compacatado há a pasta `SDL2-2.0.9` (Pode ser necessário descompactá-lo duas vezes). Coloque essa pasta `SDL2-2.0.9` em `C:\Users\Public\` (ficará `C:\Users\Public\SDL2-2.0.9\`).

**Obs:** Esse procedimento funciona também em computadores públicos (como os dos laboratórios da UFRPE).



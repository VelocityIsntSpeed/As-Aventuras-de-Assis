// Dados de um estagio
struct Estagio
{
    // String que define como vai ser o level
    char stringDeLevel[STR_LVL_TAM_MAX];
    /*

    ============================================================================
    ================[[[[ INSTRUCOES DE EDICAO DE MAPA ]]]]======================
    ============================================================================

     '.'     =   TILE_chao
     '#'     =   TILE_parede
     'I'     =   TILE_paredeInvisivel
     'E'     =   TILE_chao com inimigo inicialmente
     'h'     =   TILE_esconderijo
     'H'     =   TILE_esconderijo com inimigo
     'f'     =   TILE_final
    Resto    =   TILE_vazio


    A string do mapa pode ser de qualquer tamanho (existe tamanho maximo, mas ele eh grande).
    Eh recomendado editar este arquivo com um editor de texto utilizando uma fonte quadrada.

    Se tiver algo de errado com a string, pode aparecer mensagens de erro
    no terminal, entao preste atencao nisso.

    */


    // Posicao na qual o jogador comeca
    Vector2 spawnPos;
};




//[ ESTAGIO 1 ]================================================================
struct Estagio estagio1 = {

.stringDeLevel =

//        10        20        30        40        50        60        70        80
//        |         |         |         |         |         |         |         |
//23456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|
"#######################################\n" // 1
"#######################################\n" // 2
"#############....######################\n" // 3
"############.E....#####################\n" // 4
"############......###.................I\n" // 5
"############.......#..................I\n" // 6
"############..........E...............I\n" // 7
"############......##.....##############\n" // 8
"############...######...###############\n" // 9
"############...######...##...........##\n" //10
"############hhh######...##...E...E...##\n" //11
"############hhh######...##...........##\n" //12
"############...######...##...........##\n" //13
"#.......####...######...##...........##\n" //14
"#....E..####...######...########.....##\n" //15
"#.......####...######...########...####\n" //16
"#..............######.E............#...f\n" //17
"#..............######..............#...f\n" //18
"#.E....#####..E######...........E..#..#\n" //19
"#......#############################..#\n" //20
"#......#############################..#\n" //21
"#......####...######################..#\n" //22
"#......####.#.######################..#\n" //23
"#.........E.#E#######......E.........E#\n" //24
"#......######.#######.................#\n" //25
"#......######.....E.............E.....#\n" //26
"#######################################\n" //27




, // <-- Nao deletar essa virgula

// Posicao inicial do jogador
.spawnPos = CentroDaTile(35, 5)
//ele eh gerado no bloco 36,6

};

struct Estagio estagio2 = {

.stringDeLevel =

//        10        20        30        40        50        60        70        80
//        |         |         |         |         |         |         |         |
//23456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|
"#############################ff########\n" // 1
"#########.........###########..########\n" // 2
"#########....E....###########E.########\n" // 3
"#########.........###.............#####\n" // 4
"#########.........###....E..hhhh..#####\n" // 5
"#########.E.....E...........hHHh..#####\n" // 6
"#########...................hHHh..#####\n" // 7
"#########.........###....E..hhhh..#####\n" // 8
"#########...E.....###............E#####\n" // 9
"############...########################\n" //10
"############...########################\n" //11
"############...##########...E.........#\n" //12
"############...##.....###......S......#\n" //13
"############...##.E...###.............#\n" //14
"####HHh#####...##.....###.............#\n" //15
"####hhh#####...##.....######..#######.#\n" //16
"I......#####...##...E..............##.#\n" //17
"###....#####.......................##E#\n" //18
"####...#####.......................##.#\n" //19
"#####..##############################.#\n" //20
"#####..##############################.#\n" //21
"#####..#####...................E...##.#\n" //22
"#####.....##........E...........E..##.#\n" //23
"#####...E.......................E.....#\n" //24
"#####.................E.........E..####\n" //25
"#####.....##...................E...####\n" //26
"#######################################\n" //27




, // <-- Nao deletar essa virgula

// Posicao inicial do jogador
.spawnPos = CentroDaTile(1, 16)

};

struct Estagio estagio3 = {

.stringDeLevel =

//        10        20        30        40        50        60        70        80
//        |         |         |         |         |         |         |         |
//23456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|
"#######################################\n" // 1
"#######################################\n" // 2
"##S........E......########hHhHhHhHh#####\n" // 3
"##............E...########H...f...H####\n" // 4
"##..#####.........########h.......h####\n" // 5
"##..#####.E.......########H.......H####\n" // 6
"##.E#####......E..########h.......h####\n" // 7
"##..#####.........########H.......H####\n" // 8
"##..#####.........########hHh...hHh####\n" // 9
"##..########...##############...#######\n" //10
"##..########...##############...#######\n" //11
"##..########...##############..E.....##\n" //12
"##..########...##.....####.E.........##\n" //13
"##E.########.E.##.....####.........E.##\n" //14
"##..########...##.S.E.####.....##....##\n" //15
"##..########...##.....#####....##....h#\n" //16
"##.....#####...##.........E.........#h#\n" //17
"##...EE#####..E................E...##h#\n" //18
"#####..#####......E...............###h#\n" //19
"#####..##############################h#\n" //20
"#####..##############################h#\n" //21
"#####..#####.........E.........######h#\n" //22
"#####..#####.....S.............hhhhhhh#\n" //23
"#####..........................########\n" //24
"#####.E................E...##..########\n" //25
"############E..............##..########\n" //26
"#############################II########\n" //27




, // <-- Nao deletar essa virgula

// Posicao inicial do jogador
.spawnPos = CentroDaTile(30, 24)
//ele eh gerado no bloco 3,18

};
;;;;;



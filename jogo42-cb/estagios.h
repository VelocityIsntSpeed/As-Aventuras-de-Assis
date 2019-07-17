// Dados de um estagio
struct Estagio
{
    // String que define como vai ser o level
    const char stringDeLevel[STR_LVL_TAM_MAX];
    /*

    ============================================================================
    ================[[[[ INSTRUCOES DE EDICAO DE MAPA ]]]]======================
    ============================================================================

     '.'     =   TILE_chao
     '#'     =   TILE_parede
     'I'     =   TILE_paredeInvisivel
     'E'     =   TILE_chao com inimigo inicialmente
    Resto    =   TILE_vazio


    A string do mapa pode ser de qualquer tamanho (existe tamanho maximo, mas ele eh grande).
    Eh recomendado editar este arquivo com um editor de texto utilizando uma fonte quadrada.

    Se tiver algo de errado com a string, pode aparecer mensagens de erro
    no terminal, entao preste atencao nisso.

    */


    // Posicao na qual o jogador comeca
    Vector2 spawnPos;
};



/* Define qual level vai ser carregado. Isso eh temporario, ate ter o codigo
       de troca de level. */
    #define ESTAGIO estagio1



//[ ESTAGIO 1 ]================================================================
struct Estagio estagio1 = {

.stringDeLevel =

//        10        20        30        40        50        60        70        80
//        |         |         |         |         |         |         |         |
//23456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|
"#######################################\n" // 1
"#.......#.......#.....#....E#.....#####\n" // 2
"#.E...E.#............................##\n" // 3
"#.......#..............E.............##\n" // 4
"#E.E..E.#...###...###..E###..........I.\n" // 5
"#.......#...###...###...###..........I.\n" // 6
"#.......#................E...........I.\n" // 7
"#.......#...............E..EEE.......##\n" // 8
"#.......#.......#.....#.....#.....#####\n" // 9
"##.#######...######.###################\n" //10
"#............####.....#################\n" //11
"#............####......####...E..#.E..#\n" //12
"###########..#####......###...E..#...E#\n" //13
"#............#####.......##E..........#\n" //14
"#......###########.......#....E.....E.#\n" //15
"#......#...#....####.......#####..#####\n" //16
"#......#..E#......###.....E...#E...####\n" //17
"#......#...........###E.......E...E#...\n" //18
"##.#.###E..###......###.......E....#...\n" //19
"##.#.#....##.#.......###..E...#.E..#..#\n" //20
"##.#.#...#..E#...#....##############..#\n" //21
"##.#.#.#.#.###.#...#..........#....#..#\n" //22
"##.#.#...#.#..........................#\n" //23
"##.#####.#.#####.#....................#\n" //24
"#..............##.....................#\n" //25
"#E.#...#..########....................#\n" //26
"#######################################\n" //27




, // <-- Nao deletar essa virgula

// Posicao inicial do jogador
.spawnPos = CentroDaTile(35, 5)

};







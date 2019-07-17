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
"#......E#.......#.#...#.E..E#.....#####\n" // 2
"#..E....#.E.......#..................##\n" // 3
"#.E..E..#.........#E....E............##\n" // 4
"#E......#...###...###...###.E........I.\n" // 5
"#.......#...###E..###...###..........I.\n" // 6
"#.......#................E...........I.\n" // 7
"#.....E.#.......#.......E..EEE.......##\n" // 8
"#.E.....#.E.....#.....#.#...#.....#####\n" // 9
"#..#######...##########.###############\n" //10
"#.............###.....#.###############\n" //11
"#...............#.E...#.#........E....#\n" //12
"############....#...E.#.#...E.......E.#\n" //13
"#........###....#.....#.#.............#\n" //14
"#....E....##....#E....#.#E...E........#\n" //15
"#....E.....#....#.......########..#####\n" //16
"#.E....#......E.#E............#....#...I\n" //17
"#......#........#.E...#...........E#...I\n" //18
"#......#...#.E.E#.....#.........E..#..#\n" //19
"#...E..#################......#....#..#\n" //20
"##...#...###########################..#\n" //21
"#..#...#...#...#...##...E..........#..#\n" //22
"#..................E..........E....#..#\n" //23
"##...#...#.###...#.....E..............#\n" //24
"#..........................E.....E....#\n" //25
"#.E#...#.#.#...#....E........E........#\n" //26
"#######################################\n" //27




, // <-- Nao deletar essa virgula

// Posicao inicial do jogador
.spawnPos = CentroDaTile(35, 5)

};







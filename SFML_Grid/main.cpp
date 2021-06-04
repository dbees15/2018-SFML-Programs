#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

const unsigned int ARRAYSIZE=15;
const unsigned int CELLSIZE=40;

enum class Direction
{
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT,
    D_STOP,
};

enum class EntityType
{
    Player,
    Enemy,
    Wall,
    Empty
};


struct ArrayCell
{
    EntityType state;
    sf::RectangleShape cell;
};

struct Entitiy
{
    int x;
    int y;
    Direction waytraveling;
    EntityType type;
};

struct Grid
{
    ArrayCell Tileset[ARRAYSIZE][ARRAYSIZE];
    Entitiy entmanipulator;
};

ArrayCell cellInitializer(ArrayCell x);
Grid arrayIniializer(Grid x);
Grid positionSetter(Grid x);
sf::Color gridColorSetter(Grid g,int x,int y);
Entitiy Movement(Entitiy x);
Entitiy entityInitializer(Entitiy ent, EntityType ty);

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 700), "SFML-Test");
    Grid TileMap;
    Entitiy player;
    entityInitializer(player,EntityType::Player);
    TileMap=arrayIniializer(TileMap);
    TileMap=positionSetter(TileMap);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.waytraveling=Direction::D_LEFT;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.waytraveling=Direction::D_RIGHT;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.waytraveling=Direction::D_UP;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.waytraveling=Direction::D_DOWN;
        }
        TileMap.Tileset[player.x][player.y].state=EntityType::Empty;
        player = Movement(player);
        TileMap.Tileset[player.x][player.y].state=EntityType::Player;


        window.clear();
        for(int i=0;i<ARRAYSIZE;i++)
        {
            for(int e=0;e<ARRAYSIZE;e++)
            {
                TileMap.Tileset[e][i].cell.setFillColor(gridColorSetter(TileMap,e,i));
                window.draw(TileMap.Tileset[e][i].cell);
            }

        }

        window.display();

    }

    return 0;
}

ArrayCell cellInitializer(ArrayCell x)  //sets cell defaults
{
    x.state=EntityType::Empty;
    x.cell.setSize(sf::Vector2f(CELLSIZE,CELLSIZE));
    x.cell.setOutlineThickness(1);
    x.cell.setOutlineColor(sf::Color::Black);
    return x;
}

Grid arrayIniializer(Grid x)    //Uses cellInitializer() on entire array, setting default values;
{
    for(int i=0;i<ARRAYSIZE;i++)
    {
        for(int e=0;e<ARRAYSIZE;e++)
        {
            x.Tileset[e][i]=cellInitializer(x.Tileset[e][i]);
        }

    }

    return x;
}

Grid positionSetter(Grid x) //Loop which initializes the position of all cells
{
    int xpos=0;
    int ypos=0;
    for(int i=0;i<ARRAYSIZE;i++)
    {
        for(int e=0;e<ARRAYSIZE;e++)
        {
            x.Tileset[e][i].cell.setPosition(xpos,ypos);
            xpos+=CELLSIZE;
        }
    ypos+=CELLSIZE;
    xpos=0;
    }
    return x;
}



sf::Color gridColorSetter(Grid g,int x,int y)   //sets the color of a cell depending on its isOn state
{
    if(g.Tileset[x][y].state!=EntityType::Empty)
    {
//        if


    }
    else
    {
        return sf::Color::White;
    }
}

Entitiy Movement(Entitiy x) //Actually changes the coordinates of the entity and prevents it from leaving the array
{
    switch(x.waytraveling)
    {
    case Direction::D_DOWN:
        x.y+=1;
        break;
    case Direction::D_UP:
        x.y-=1;
        break;
    case Direction::D_LEFT:
        x.x-=1;
        break;
    case Direction::D_RIGHT:
        x.x+=1;
        break;
    }
    if(x.x<0)   //the next checks prevent entity from leaving array
        ++x.x;
    else if(x.x>=ARRAYSIZE)
        --x.x;
    if(x.y<0)
        ++x.y;
    else if(x.y>=ARRAYSIZE)
        --x.y;
    //std::cout<<x.x<<", "<<x.y<<"\n";
    //^^UNCOMMENT FOR DEBUG: prints coordinates in console
    return x;
}
/*
Grid tileMovement(grid x)
{

}
*/

Entitiy entityInitializer(Entitiy ent, EntityType ty)
{
    ent.x=0;
    ent.y=0;
    ent.waytraveling=Direction::D_STOP;
    ent.type=ty;
    return ent;
}

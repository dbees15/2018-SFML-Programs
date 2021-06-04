#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

//----------CONSTANTS&ENUMTYPE
const unsigned short WINDOW_SIZE=750;
const unsigned short VERT_NUM=4;
const unsigned short SHAPE_SIZE=750;
const unsigned short REFRESH_RATE_MS=20;
const bool DEBUG=false;

enum class RGB
{
    Red,
    Green,
    Blue,
    NA
};

//----------STRUCTURES
struct ColIdentifier
{
    RGB colID;
    sf::Color col;
};

struct VertData
{
    bool st_swtch[VERT_NUM];
    ColIdentifier vertexcol[VERT_NUM];
};

//----------FUNCTION PROTOTYPES
sf::VertexArray colorInitializer(sf::VertexArray x,int vertnum,sf::Color col);
sf::VertexArray colorInitializer(sf::VertexArray x,int vertnum,sf::Color col);
ColIdentifier colorStart(ColIdentifier x, RGB col);
ColIdentifier colorLoop(ColIdentifier x,RGB startcolor,bool startswitch);
ColIdentifier redSegment(ColIdentifier x);
ColIdentifier greenSegment(ColIdentifier x);
ColIdentifier blueSegment(ColIdentifier x);
bool startSwitcher(bool swch,sf::Color x);
VertData VD_initializer(VertData x);
VertData VD_colorChanger(sf::VertexArray x,VertData dta);
//-----------------------------


const RGB VERTEX_COLORS[VERT_NUM]={RGB::Blue,RGB::Red,RGB::Blue,RGB::Red};    //**CHANGE VALUES TO CHANGE VERTEX STARTING COLORS**

int main()
{
    sf::Clock time;     //starts clock
    sf::Time elapsed;   //elapsed time variable
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "RGB!");

    sf::VertexArray vertex(sf::Quads,VERT_NUM);
    VertData vertexdata;
    vertex[0].position = sf::Vector2f(10,10);
    vertex[1].position = sf::Vector2f(SHAPE_SIZE,10);
    vertex[2].position = sf::Vector2f(SHAPE_SIZE,SHAPE_SIZE);
    vertex[3].position = sf::Vector2f(10,SHAPE_SIZE);
    vertexdata=VD_initializer(vertexdata);
    vertex=colorInitializer(vertex,VERT_NUM,sf::Color(0,0,0));



    while (window.isOpen())
    {
        elapsed=time.getElapsedTime();  //updates passed time
        if(elapsed.asMilliseconds()%REFRESH_RATE_MS==0)         //Changes color depending only on refresh rate
        {
            vertexdata=VD_colorChanger(vertex,vertexdata);
            vertex[0].color=vertexdata.vertexcol[0].col;
            vertex[1].color=vertexdata.vertexcol[1].col;
            vertex[2].color=vertexdata.vertexcol[2].col;
            vertex[3].color=vertexdata.vertexcol[3].col;
            if(DEBUG==true)                                     //Debug info, can be turned off with const DEBUG
            {
                std::cout<<" ("<<static_cast<int>(vertexdata.vertexcol[0].colID)<<") ";
                std::cout<<static_cast<int>(vertex[0].color.r)<<" "<<static_cast<int>(vertex[0].color.g)<<" "<<static_cast<int>(vertex[0].color.b)<<"\n";
            }
        }

        sf::Event event;    //event system for next 7 lines, can be expanded upon for more functionality
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(vertex);    //draws the vertex
        window.display();
    }

    return 0;
}

sf::VertexArray colorInitializer(sf::VertexArray x,int vertnum,sf::Color col)   //initializes the vertex array colors of the vertexArray. anything but (0,0,0) for this program will BREAK IT
{
    for(int e=0;e<vertnum;e++)
    {
        x[e].color=col;
    }
    return x;
}

VertData VD_colorChanger(sf::VertexArray x,VertData dta)    //VertexData structure function. Used in int main to set colors for each vertex. Has capacity for more then 4 vertexes.
{
    for(int e=0;e<VERT_NUM;e++)
    {
        dta.st_swtch[e]= startSwitcher(dta.st_swtch[e],x[0].color);
        dta.vertexcol[e]= colorLoop(dta.vertexcol[e],VERTEX_COLORS[e],dta.st_swtch[e]);
    }
    return dta;
}

VertData VD_initializer(VertData x) // deals with the VertexData structure. initializes the variables and most importantly, sets all start switches to true.
{
    for(int e=0;e<(sizeof(x.st_swtch)/sizeof(x.st_swtch[0]));e++)
    {
        x.st_swtch[e]= true;
        x.vertexcol[e].colID= RGB::Red;
    }
    return x;
}


ColIdentifier colorStart(ColIdentifier x, RGB col)  //Starts off the color loop, only works if the other colors are == 0
{
    if(col==RGB::Red&&(x.col.g==0&&x.col.b==0))
    {
        x.col.r+=1;
        x.colID=RGB::Red;
    }
    if(col==RGB::Green&&(x.col.r==0&&x.col.b==0))
    {
        x.col.g+=1;
        x.colID=RGB::Green;
    }
    if(col==RGB::Blue&&(x.col.g==0&&x.col.r==0))
    {
        x.col.b+=1;
        x.colID=RGB::Blue;
    }
    return x;
}

ColIdentifier colorLoop(ColIdentifier x,RGB startcolor,bool startswitch)    //the "heart" of the program; increments all segments of the color and is the only user of colorStart
{
    if(startswitch==true)
    {
        x=colorStart(x,startcolor);
    }
    else
    {
        x=redSegment(x);
        x=greenSegment(x);
        x=blueSegment(x);
    }
    return x;
}

ColIdentifier redSegment(ColIdentifier x)   //increments the red segment of a color. Will not work if above 255 and will return green for colID
{
    if(x.colID==RGB::Red)
    {
        if(x.col.r==255)
        {
            x.colID=RGB::Green;
            return x;
        }
        else if(x.col.r>=0&&x.col.b>0)
        {
            x.col.r++;
            x.col.b--;
        }
    }
    return x;
}
ColIdentifier greenSegment(ColIdentifier x) //increments the green segment of a color. Will not work if above 255 and will return blue for colID
{
    if(x.colID==RGB::Green)
    {
        if(x.col.g==255)
        {
            x.colID=RGB::Blue;
            return x;
        }
        else if(x.col.g>=0&&x.col.r>0)
        {
            x.col.g++;
            x.col.r--;
        }
    }
    return x;
}
ColIdentifier blueSegment(ColIdentifier x)  //increments the blue segment of a color. Will not work if above 255 and will return red for colID
{
    if(x.colID==RGB::Blue)
    {
        if(x.col.b==255)
        {
            x.colID=RGB::Red;
            return x;
        }
        else if(x.col.b>=0&&x.col.g>0)
        {
            x.col.b++;
            x.col.g--;
        }
    }
    return x;
}


bool startSwitcher(bool swch,sf::Color x)   //switches off the starter function once one color gets to 255
{
    if(x.r==255||x.g==255||x.b==255)
    {
        swch=false;
    }
    return swch;
}

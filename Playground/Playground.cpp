#include "Playground.h"
int main()
{
	rapidjson::Document Cards = read_json( "data/1_ROGUE.json" );
    /*for(int c1=0;c1<419;++c1)
    {
        Cards.Erase( Cards.Begin() );
    }
    for(int c1=0;c1<434-419-1;++c1)
    {
        Cards.Erase( Cards.Begin()+1 );
    }*/
    //for(int c1=0;c1<Cards.Size()-2;++c1)
    //{ 
        Cards.Erase( Cards.Begin()+2 );
    //}
    write_json(Cards,"data/1_ROGUE.json");
	return 0;
}

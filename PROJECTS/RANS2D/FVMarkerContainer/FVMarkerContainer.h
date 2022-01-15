#ifndef FVMarker_h
#define FVMarker_h
#pragma pack(1)

#include <string.h>
#include <stdlib.h>

//INCLUDES_BEGIN
//INCLUDES_END

typedef struct
{
    int  size;
    int  *iBeg;
    int  *iEnd;
    char **name;
}
FVMarkerContainer;

void init__FVMarkerContainer(void *_self);
void delete__FVMarkerContainer(void *_self);
void create__FVMarkerContainer(void *_self);

#endif
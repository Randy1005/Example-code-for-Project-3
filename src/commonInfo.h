#ifndef COMMONINFO_H
#define COMMONINFO_H

#define ZIGGY_ID 999
#define SLIME_ID 1
#define BULLET_ID 2
#define PLATFORM_ID 3
#define GROUND_ID 4

typedef struct userDataStruct{
    int id;
    void *charactePtr;
    int characterIndex;
}udStruct;


#endif // COMMONINFO_H

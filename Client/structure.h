#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <map>

struct KVList
{
    map<string, string> KVData;
    string              KVGroup;
};

typedef map<string, int> KVRt;

#endif // STRUCTURE_H

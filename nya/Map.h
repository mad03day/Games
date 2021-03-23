#pragma once
#include <fstream>
#include "Block.h"
#include <time.h>

using namespace std;

#define Map_h
#ifdef Map_h

class Map
{
public:
    /*int seed;
    string name = { "map.txt" };
    ofstream map_file;
    void save_block_in_file(Block blk);*/

    float** Create_map(int height, int width);

private:
   
};

#define MAX_OCTAVES 15

class Perlin2D
{
private:
    unsigned long seed = 1;
    unsigned octaves;

    double value(long x, long y) const;

    double value2(long x, long y) const;

    inline long fastFloor(float x) const;

    float LinearInterpolate(float a, float b, float c) const;

    inline float dot(float gx, float gy, float x, float y) const;

    float InterpotatedNoise(float x, float y) const;

public:

    Perlin2D();

    Perlin2D(unsigned _octaves);

    float get(float x, float y) const;

    void setOctaves(float _octaves);

    unsigned getOctaves() const;

};


#endif
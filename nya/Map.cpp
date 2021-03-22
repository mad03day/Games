#include "Map.h"

void Map::save_block_in_file(Block blk)
{
    map_file.open(name, ofstream::app);
    //map_file << blk.id << " " << blk.x << " " << blk.y << " " << blk.colizion << "\n";
    map_file.close();
}

/*---------------------------------------------------------------------------------------------*/

double Perlin2D::value(long x, long y) const
{
    unsigned long n = x + y * 563;
    n = ((n + seed) << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + seed) & 0x7fffffff) / 1073741824.0);
}

double Perlin2D::value2(long x, long y) const
{
    unsigned long n = x + y * 367;
    n = ((n + seed) << 11) ^ n;
    return (1.0 - ((n * (n * n * 20183 + 815279) + seed) & 0x7fffffff) / 1073741824.0);
}

inline long Perlin2D::fastFloor(float x) const
{
    return x > 0 ? (long)x : (long)x - 1;
}

float Perlin2D::LinearInterpolate(float a, float b, float c) const
{
    return a + c * (b - a);
}

inline float Perlin2D::dot(float gx, float gy, float x, float y) const
{
    return gx * x + gy * y;
}

float Perlin2D::InterpotatedNoise(float x, float y) const
{
    long integerX = fastFloor(x);
    long integerY = fastFloor(y);
    float fx = x - integerX;
    float fy = y - integerY;
    float tx = fx * fx * fx * (fx * (fx * 6 - 15) + 10);
    float ty = fy * fy * fy * (fy * (fy * 6 - 15) + 10);
    return LinearInterpolate(LinearInterpolate(dot(value(integerX, integerY), value2(integerX, integerY), fx, fy), dot(value(integerX + 1, integerY), value2(integerX + 1, integerY), fx - 1, fy), tx),
        LinearInterpolate(dot(value(integerX, integerY + 1), value2(integerX, integerY + 1), fx, fy - 1), dot(value(integerX + 1, integerY + 1), value2(integerX + 1, integerY + 1), fx - 1, fy - 1), tx), ty);
}

Perlin2D::Perlin2D() : octaves(1)
{
    seed = rand();
}

Perlin2D::Perlin2D(unsigned _octaves) : octaves(_octaves)
{
    seed = rand();
}

float Perlin2D::get(float x, float y) const
{
    float frequency = 0.01f, amplitude = 1.0f, total = 0.0f, scale = 0.0f;
    for (unsigned i = 0; i < octaves; ++i)
    {
        total += InterpotatedNoise(x * frequency, y * frequency) * amplitude;
        scale += amplitude;
        frequency *= 2.0f;
        amplitude *= 0.5f;
    }
    return total / scale;
}

void Perlin2D::setOctaves(float _octaves)
{
    octaves = _octaves;
    if (_octaves < 1)
        octaves = 1;
    else if (_octaves > MAX_OCTAVES)
        octaves = MAX_OCTAVES;
}

unsigned Perlin2D::getOctaves() const
{
    return octaves;
}

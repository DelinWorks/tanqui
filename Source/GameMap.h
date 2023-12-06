#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "axmol.h"
USING_NS_AX;

#include <string>
#include <vector>

class GameMap : public Node
{
public:
    GameMap(const std::string &tilesetFilename, const std::vector<std::vector<int>> &mapData);
    static GameMap *create(const std::string &tilesetFilename, const std::vector<std::vector<int>> &mapData);
    virtual bool init() override;

private:
    std::string tilesetFilename;
    std::vector<std::vector<int>> mapData;
    SpriteBatchNode *spriteBatchNode;

    void buildMap();
};

#endif // __GAMEMAP_H__

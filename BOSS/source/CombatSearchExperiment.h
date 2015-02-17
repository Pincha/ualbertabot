#pragma once

#include "BOSS.h"
#include "GUITools.h"
#include "JSONTools.h"
#include <memory>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

namespace BOSS
{

class CombatSearchExperiment
{
    std::string                 _name;
    CombatSearchParameters      _params;
    RaceID                      _race;
    std::vector<std::string>    _searchTypes;

    RaceID                      _enemyRace;
    BuildOrder                  _enemyBuildOrder;

public:

    CombatSearchExperiment();
    CombatSearchExperiment(const std::string & name, const rapidjson::Value & experimentVal, std::map< std::string, GameState > & stateMap, std::map< std::string, BuildOrder > & buildOrderMap);

    void run();
};
}
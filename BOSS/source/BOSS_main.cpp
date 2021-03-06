#include "BOSS.h"
#include "BOSSExperiments.h"
#include "BuildOrderTester.h"
#include "GUI.h"

using namespace BOSS;

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

BOSS::BOSSExperiments experiments;
std::string returnString("TestReturn");

void mainLoop()
{


    GUI::Instance().OnFrame();
}

extern "C" 
{
const char * ResetExperiment(char * paramString)
{
    std::cout << "Param String Received" << std::endl;

    std::string params(paramString);

    experiments = BOSS::BOSSExperiments();

    if (params.length() == 0)
    {
        #ifndef EMSCRIPTEN
            experiments.loadExperimentsFromFile("../asset/config/webconfig.txt");
        #else
            experiments.loadExperimentsFromFile("asset/config/webconfig.txt");
        #endif
    }
    else
    {
        experiments.loadExperimentsFromString(params);
    }

    if (experiments.getVisExperiments().size() > 0)
    {
        GUI::Instance().SetVisExperiment(experiments.getVisExperiments()[0]);
    }
 
    return returnString.c_str();
}
}

void doCombatExperiment()
{


    BOSS::BOSSExperiments exp;
    exp.loadExperimentsFromFile("../asset/config/config.txt");

    for (size_t i(0); i < exp.getCombatSearchExperiments().size(); ++i)
    {
        exp.getCombatSearchExperiments()[i].run();
    }
}

int main(int argc, char *argv[])
{
    BOSS::init();
    
    doCombatExperiment();
/*
    ResetExperiment("");

    if (experiments.getVisExperiments().size() > 0)
    {
        GUI::Instance().OnStart();
        GUI::Instance().SetVisExperiment(experiments.getVisExperiments()[0]);
    }

#ifndef EMSCRIPTEN
    while (true)
    {
        mainLoop();
    }
#else
    emscripten_set_main_loop(mainLoop,0,true);
#endif*/

    return 0;
}


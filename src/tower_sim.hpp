#pragma once

#include "aircraft_manager.hpp"

#include <memory>

class Aircraft;
struct AircraftType;
class Airport;

class TowerSimulation
{
private:
    bool help        = false;
    Aircraft_factory* factory = nullptr;
    AircraftManager manager;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_keystrokes();
    void display_help() const;

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};

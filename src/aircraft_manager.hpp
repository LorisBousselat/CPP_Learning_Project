#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"
#include "terminal.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int crashed_counter = 0;

public:
    void add(std::unique_ptr<Aircraft> aircraft);
    bool update() override;
    int countAirline(const std::string& airline);
    void crash(){crashed_counter += 1;};
    int crash_count()const {return crashed_counter;};
    unsigned int get_required_fuel() const;
};
#include "aircraft_manager.hpp"

#include <algorithm>
#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    // for (auto aircraft_it = aircrafts.begin(); aircraft_it != aircrafts.end();)
    // {
    //     // On doit déréférencer 2x pour obtenir une référence sur l'Aircraft : une fois pour déréférencer
    //     // l'itérateur, et une deuxième fois pour déréférencer le unique_ptr.
    //     auto& aircraft = **aircraft_it;
    //     if (aircraft.update())
    //     {
    //         ++aircraft_it;
    //     }
    //     else
    //     {
    //         aircraft_it = aircrafts.erase(aircraft_it);
    //     }
    // }

    // TASK-02 utilisation de remove_if
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](const std::unique_ptr<Aircraft>& a) {return !a->update();}),
                    aircrafts.end());

    return true;
}

int AircraftManager::countAirline(const std::string& airline)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(), [&airline](const std::unique_ptr<Aircraft>& a){
        return a->get_flight_num().find(airline) != std::string::npos;
    });
}

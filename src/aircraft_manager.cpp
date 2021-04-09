#include "aircraft_manager.hpp"

#include <algorithm>
#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](const auto& a, const auto& b)
              {
                  if (a->has_terminal())
                  {
                      return true;
                  }
                  if (b->has_terminal())
                  {
                      return false;
                  }

                  return a->get_fuel() < b->get_fuel();
              });
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
                                   [](const std::unique_ptr<Aircraft>& a) { return !a->update(); }),
                    aircrafts.end());

    //*** Affichage de la liste ***
    // std::cout << "******************" << std::endl;
    // for(auto& a : aircrafts)
    // {
    //     auto term = a->has_terminal() ? "Reserved" : "NotReserved";
    //     std::cout << term << " / fuel : " << a->get_fuel() <<std::endl;
    // }
    // return true;
}

int AircraftManager::countAirline(const std::string& airline)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [&airline](const std::unique_ptr<Aircraft>& a)
                         { return a->get_flight_num().find(airline) != std::string::npos; });
}

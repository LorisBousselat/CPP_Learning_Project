#pragma once
#include "aircraft_manager.hpp"
#include "airport.hpp"

class Aircraft_factory
{
private:
    Airport* airport              = nullptr;
    AircraftManager manager;
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    void init_airport()
    {
        assert(!airport);
        airport = new Airport { manager, one_lane_airport, Point3D { 0, 0, 0 },
                                new img::Image { one_lane_airport_sprite_path.get_full_path() } };

        GL::move_queue.emplace(airport);
    }

public:
    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type) const
    {
        assert(airport); // make sure the airport is initialized before creating aircraft

        const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
        const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
        const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
        const Point3D direction = (-start).normalize();

        // La gestion des Aircrafts se fait maintenant via des unique_ptr de bout en bout.
        return std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
    }

    [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft() const
    {
        return create_aircraft(*(aircraft_types[rand() % 3]));
    }

    Aircraft_factory() { init_airport(); }
    ~Aircraft_factory() { delete airport; };
};
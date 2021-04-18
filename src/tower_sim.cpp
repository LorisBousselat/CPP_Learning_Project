#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"
#include "aircraft_factory.hpp"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    create_keystrokes();

    // On doit ajouter le manager à la move_queue, afin que timer() appelle bien sa fonction update() à chaque
    // frame.
    GL::move_queue.emplace(&manager);
}

TowerSimulation::~TowerSimulation()
{
    delete factory;
}

// On doit supprimer le const sur create_keystrokes, car on a maintenant des inputs succeptibles de modifier
// le contenu de la simulation.
void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { manager.add(factory->create_random_aircraft()); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('m', [this]() {std::cout<<manager.crash_count()<<" planes crashed"<<std::endl; });

    // TASK_0 C-2: framerate control
    // Framerate cannot equal 0 or the program would get stuck / crash.
    // Also, in a "real" program, the maximal framerate should always be capped (you can see why if you do the
    // bonus part).
    GL::keystrokes.emplace('z', []() { GL::ticks_per_sec = std::max(GL::ticks_per_sec - 1u, 1u); });
    GL::keystrokes.emplace('a', []() { GL::ticks_per_sec = std::min(GL::ticks_per_sec + 1u, 180u); });

    // TASK_0 C-2: pause
    // Since the framerate cannot be 0, we introduce a new variable to manage this info.
    // Also, it would make no sense to use the framerate to simulate the pause, cause how would we unpause if
    // the program is not running anymore ?
    GL::keystrokes.emplace('p', []() { GL::is_paused = !GL::is_paused; });

    //TASK-2 B-2 
    for (int i = 0; i <= 7; i++)
    {
        GL::keystrokes.emplace(std::to_string(i)[0],
                               [this, i]()
                               {
                                   std::cout << airlines[i]
                                             << " has : " << manager.countAirline(airlines[i])
                                             << " airplanes" << std::endl;
                               });
    }
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    // TASK-02 utilisation de structured binding
    for (const auto& [touche, action] : GL::keystrokes)
    {
        std::cout << touche << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    factory = new Aircraft_factory();
    init_aircraft_types();

    GL::loop();
}

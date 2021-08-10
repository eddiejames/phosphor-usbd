#include "controller.hpp"

#include <filesystem>

#include <sdbusplus/bus.hpp>

namespace fs = std::filesystem;

static bool createController(sdbusplus::bus::bus &bus, const fs::path &dir, const std::string &num)
{

}

static bool findAndCreateControllers(sdbusplus::bus::bus &bus)
{
    bool foundOne(false);
    fs::path dir("/sys/bus/usb/devices/");

    if (!fs::is_directory(dir))
    {
        return false;
    }

    for (auto &p : fs::directory_iterator(dir, fs::directory_options::follow_directory_symlink))
    {
        std::string s = p.path().filename().string();

        if (s.find("usb") == 0)
        {
            std::string n = s.substr(3);

            if (createController(bus, p.path(), n))
            {
                foundOne = true;
            }
        }
    }

    return foundOne;
}

int main()
{
    std::vector<Controller> controllers;
    auto bus = sdbusplus::bus::new_default();

    return 0;
}

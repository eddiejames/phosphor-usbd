#include <xyz/openbmc_project/State/USB/server.hpp>

#include <sdbusplus/bus.hpp>

namespace phosphor
{
namespace usbd
{

namespace fs = std::filesystem;
using ControllerInherit = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::State::server::USB>;

class Controller : ControllerInherit
{
  public:
    Controller(const fs::path& path, sdbusplus::bus::bus &bus, const char *objPath) : ControllerInherit(bus, objPath), path(path), bus(bus)
    {
      discoverInitialState();
    }

    State Status(State state) override;

  private:
    void discoverInitialState();

    const fs::path path;

    sdbusplus::bus::bus &bus;
};

} // namespace usbd
} // namespace phosphor

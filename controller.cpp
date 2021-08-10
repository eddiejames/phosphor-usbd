#include "controller.hpp"

#include <phosphor-logging/elog-errors.hpp>
#include <phosphor-logging/log.hpp>
#include <xyz/openbmc_project/Common/error.hpp>

namespace phosphor
{
namespace usbd
{

using namespace phosphor::logging;

Controller::State Controller::Status(State state)
{
    if (state != Status) {
        log<level::INFO>()

        Status = state;
    }
}

void Controller::discoverInitialState()
{
    using InternalFailure = sdbusplus::xyz::openbmc_project::Common::Error::InternalFailure;
    int authorized;
    auto authorizedFile = path / "authorized";
    std::ifstream file(authorizedFile, std::ios::in);

    if (!file)
    {
        log<level::ERR>(fmt::format("No \"authorized\" file for USB controller {}", path).c_str());
        elog<InternalFailure>();
    }

    file >> authorized;
    if (authorized)
    {
        Status = State::Enabled;
    }
    else
    {
        Status = State::Disabled;
    }
}

} // namespace usbd
} // namespace phosphor

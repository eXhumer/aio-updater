#include <borealis.hpp>
#include <string>

#include "utils.hpp"
#include "payload.hpp"

int main(int argc, char* argv[])
{
    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

    if (!brls::Application::init("aio-updater"))
    {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    brls::TabFrame* rootFrame = new brls::TabFrame();
    rootFrame->setTitle("AIO Updater v" APP_VERSION " - powered by borealis");
    rootFrame->setIcon(BOREALIS_ASSET("icon/app_icon.jpg"));

    std::string amsHash;
    std::string amsVersion;
    std::string fwVersion;
    getAMSVersion(amsVersion);
    getAMSHash(amsHash);
    getFWVersion(fwVersion);

    brls::List* atmosTab = new brls::List();

    std::string sysInfo = "Firmware Version: " + fwVersion + "\nAtmosphere Version: " + amsVersion + "\nAtmosphere Hash: " + amsHash;
    brls::Label* sysInfoLabel = new brls::Label(brls::LabelStyle::REGULAR, sysInfo, true);
    brls::ListItem* updateAMSItem = new brls::ListItem("Update Atmosphere");
    brls::ListItem* rebootPayloadItem = new brls::ListItem("Reboot to Payload");
    // load_payload

    updateAMSItem->getClickEvent()->subscribe([](brls::View* view){
        brls::Dialog* dialog = new brls::Dialog("Are you sure you want to update Atmosphere?");

        brls::GenericEvent::Callback updateCallback = [dialog](brls::View* view){
            dialog->close();
            brls::Application::notify("Updating Atmosphere!");
        };

        brls::GenericEvent::Callback closeCallback = [dialog](brls::View* view){
            dialog->close();
        };

        dialog->addButton("Update", updateCallback);
        dialog->addButton("Cancel", closeCallback);

        dialog->setCancelable(false);

        dialog->open();
    });

    rebootPayloadItem->getClickEvent()->subscribe([](brls::View* view){
        brls::Dialog* dialog = new brls::Dialog("Are you sure you want to reboot to payload?");

        brls::GenericEvent::Callback rebootCallback = [dialog](brls::View* view){
            dialog->close();
            load_payload("/atmosphere/reboot_payload.bin");
            reboot_to_payload();
        };

        brls::GenericEvent::Callback closeCallback = [dialog](brls::View* view){
            dialog->close();
        };

        dialog->addButton("Reboot", rebootCallback);
        dialog->addButton("Cancel", closeCallback);

        dialog->setCancelable(false);

        dialog->open();
    });

    atmosTab->addView(new brls::Header("System Information", false));
    atmosTab->addView(sysInfoLabel);
    atmosTab->addView(new brls::Header("Options", false));
    atmosTab->addView(updateAMSItem);
    atmosTab->addView(rebootPayloadItem);

    rootFrame->addTab("Atmosphere", atmosTab);
    rootFrame->addSeparator();

    brls::Application::pushView(rootFrame);

    if (isSXOS())
        brls::Application::crash("The software was closed because an error occured:\nTrashOS is not supported by this application!\nThis application is only meant to be run under Atmosphere CFW!");
    else if (isReiNX())
        brls::Application::crash("The software was closed because an error occured:\nWeebOS is not supported by this application!\nThis application is only meant to be run under Atmosphere CFW!");
    else if (!isAtmosphere())
        brls::Application::crash("The software was closed because an error occured:\nUnknown CFW!\nThis application is only meant to be run under Atmosphere CFW!");

    while (brls::Application::mainLoop());

    return EXIT_SUCCESS;
}

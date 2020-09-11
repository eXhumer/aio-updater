#include <stdio.h>
#include <stdlib.h>

#include <borealis.hpp>
#include <string>

#include "utils.hpp"

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

    brls::ListItem* firstItem = new brls::ListItem("Test Item");
    brls::Label* firstLabel1 = new brls::Label(brls::LabelStyle::REGULAR, "FW Version: " + fwVersion, true);
    brls::Label* firstLabel2 = new brls::Label(brls::LabelStyle::REGULAR, "AMS Version: " + amsVersion, true);
    brls::Label* firstLabel3 = new brls::Label(brls::LabelStyle::REGULAR, "AMS Hash: " + amsHash, true);
    brls::ListItem* secondItem = new brls::ListItem("Test Item");
    brls::Label* secondLabel = new brls::Label(brls::LabelStyle::REGULAR, "Test Label", true);
    brls::ListItem* thirdItem = new brls::ListItem("Test Item");
    brls::Label* thirdLabel = new brls::Label(brls::LabelStyle::REGULAR, "Test Label", true);
    brls::ListItem* fourthItem = new brls::ListItem("Test Item");
    brls::Label* fourthLabel = new brls::Label(brls::LabelStyle::REGULAR, "Test Label", true);

    brls::List* updateAMSOptionsList = new brls::List();
    updateAMSOptionsList->addView(firstItem);
    updateAMSOptionsList->addView(firstLabel1);
    updateAMSOptionsList->addView(firstLabel2);
    updateAMSOptionsList->addView(firstLabel3);

    brls::List* updateSigOptionsList = new brls::List();
    updateSigOptionsList->addView(secondItem);
    updateSigOptionsList->addView(secondLabel);

    brls::List* updateHekateOptionsList = new brls::List();
    updateHekateOptionsList->addView(thirdItem);
    updateHekateOptionsList->addView(thirdLabel);

    brls::List* settingsOptionsList = new brls::List();
    settingsOptionsList->addView(fourthItem);
    settingsOptionsList->addView(fourthLabel);

    rootFrame->addTab("Atmosphere", updateAMSOptionsList);
    rootFrame->addTab("Sigpatches", updateSigOptionsList);
    rootFrame->addTab("Hekate", updateHekateOptionsList);
    rootFrame->addSeparator();
    rootFrame->addTab("Settings", settingsOptionsList);

    brls::Application::pushView(rootFrame);

    if (isSXOS())
    {
        brls::Application::crash("The software was closed because an error occured:\nTrashOS is not supported by this application!\nThis application is only meant to be run under Atmosphere CFW!");
    }
    else if (isReiNX())
    {
        brls::Application::crash("The software was closed because an error occured:\nWeebOS is not supported by this application!\nThis application is only meant to be run under Atmosphere CFW!");
    }
    else if (!isAtmosphere())
    {
        brls::Application::crash("The software was closed because an error occured:\nUnknown CFW!\nThis application is only meant to be run under Atmosphere CFW!");
    }

    while (brls::Application::mainLoop());
    return EXIT_SUCCESS;
}

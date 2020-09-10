#include <stdio.h>
#include <stdlib.h>

#include <borealis.hpp>
#include <string>

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

    brls::ListItem* firstItem = new brls::ListItem("Test Item");
    brls::Label* firstLabel = new brls::Label(brls::LabelStyle::REGULAR, "Test Label", true);
    brls::ListItem* secondItem = new brls::ListItem("Test Item");
    brls::Label* secondLabel = new brls::Label(brls::LabelStyle::REGULAR, "Test Label", true);
    brls::ListItem* thirdItem = new brls::ListItem("Test Item");
    brls::Label* thirdLabel = new brls::Label(brls::LabelStyle::REGULAR, "Test Label", true);
    brls::ListItem* fourthItem = new brls::ListItem("Test Item");
    brls::Label* fourthLabel = new brls::Label(brls::LabelStyle::REGULAR, "Test Label", true);

    brls::List* updateAMSOptionsList = new brls::List();
    updateAMSOptionsList->addView(firstItem);
    updateAMSOptionsList->addView(firstLabel);

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

    while (brls::Application::mainLoop());

    return EXIT_SUCCESS;
}

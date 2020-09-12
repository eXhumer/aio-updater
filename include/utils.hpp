#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>

bool getAMSHash(std::string& outHash);
bool getAMSVersion(std::string& outVersion);
bool getFWVersion(std::string& outVersion);
bool isServiceRegistered(std::string serviceStr);
bool isReiNX();
bool isSXOS();
bool isAtmosphere();
#endif

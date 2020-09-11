#include <switch.h>
#include <sstream>
#include <string>

bool getFWVersion(std::string& outVersion)
{
    Result rc;

    if (R_FAILED(rc = setsysInitialize()))
        return false;

    SetSysFirmwareVersion ver;

	if (R_FAILED(rc = setsysGetFirmwareVersion(&ver)))
		return false;

    std::stringstream outVersionStream;
    outVersionStream << ver.display_version;
    outVersion.clear();
    outVersion = outVersionStream.str();
    outVersionStream.clear();
    return true;
}

bool getAMSVersion(std::string& outVersion)
{
    Result rc;
	u64 ver;
	// u64 fullHash;
	SplConfigItem SplConfigItem_ExosphereVersion = (SplConfigItem)65000;
	// SplConfigItem SplConfigItem_ExosphereVerHash = (SplConfigItem)65003;

	if (R_FAILED(rc = splInitialize()))
		return false;

	if (R_FAILED(rc = splGetConfig(SplConfigItem_ExosphereVersion, &ver)))
        return false;

	// if (R_FAILED(rc = splGetConfig(SplConfigItem_ExosphereVerHash, &fullHash)))
	//     return false;

    u64 major = (ver >> 56) & 0xFF;
    u64 minor = (ver >> 48) & 0xFF;
    u64 patch = (ver >> 40) & 0xFF;
    std::stringstream outVersionStream;
    outVersionStream << major << ".";
    outVersionStream << minor << ".";
    outVersionStream << patch;
    outVersion.clear();
    outVersion = outVersionStream.str();
    outVersionStream.clear();
    splExit();
    return true;
}

bool getAMSHash(std::string& outHash)
{
    Result rc;
	u64 fullHash;
	SplConfigItem SplConfigItem_ExosphereVerHash = (SplConfigItem)65003;

	if (R_FAILED(rc = splInitialize()))
		return false;

	if (R_FAILED(rc = splGetConfig(SplConfigItem_ExosphereVerHash, &fullHash)))
        return false;

    std::stringstream outHashStream;
    outHashStream << std::hex << fullHash;
    outHash.clear();
    outHash = outHashStream.str();
    outHashStream.clear();
    splExit();
    return true;
}

bool isServiceRegistered(std::string serviceStr)
{
    Handle tmph = 0;
    SmServiceName serviceName = {smEncodeName(serviceStr.c_str())};
    Result rc = smRegisterService(&tmph, serviceName, false, 1);
    if(R_FAILED(rc)) return true;
    smUnregisterService(serviceName);
    return false;
}

bool isReiNX()
{
    return isServiceRegistered("rnx");
}

bool isSXOS()
{
    return isServiceRegistered("tx");
}

bool isAtmosphere()
{
    Result rc;
    if (R_FAILED(rc = splInitialize())) return false;
    u64 tmpc = 0;
    bool isAtmos = R_SUCCEEDED(splGetConfig((SplConfigItem)65000, &tmpc));
    splExit();
    return isAtmos;
}

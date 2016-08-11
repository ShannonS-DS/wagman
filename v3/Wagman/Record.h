#include <Arduino.h>
#include "Time.h"

struct Version
{
    byte major;
    byte minor;
};

struct Range
{
    int min;
    int max;
};

struct SensorStatus
{
    byte health;
    Range range;
};

class BootLog
{
public:

    BootLog(unsigned int addr);
    void init();
    
    void addEntry(time_t time);
    time_t getEntry(byte i);
    
    byte getCount() const;
    byte getCapacity() const;

private:

    byte getStart() const;
    void setStart(byte start);
    
    void setCount(byte count);

    unsigned int address;
    const byte capacity = 8;
};

namespace Record
{
    extern BootLog bootLogs[5];

    bool initialized();

    void init();

    void clearMagic();

    void getHardwareVersion(Version &version);
    void setHardwareVersion(const Version &version);

    void getFirmwareVersion(Version &version);
    void setFirmwareVersion(const Version &version);

    void getBootCount(unsigned long &count);
    void setBootCount(const unsigned long &count);
    void incrementBootCount();

    void getLastBootTime(time_t &time);
    void setLastBootTime(const time_t &time);

    void setDeviceEnabled(byte device, bool enabled);
    bool getDeviceEnabled(byte device);

    void getDeviceBootTime(byte device, time_t &time);
    void setDeviceBootTime(byte device, const time_t &time);

    byte getRelayState(byte port);
    void setRelayState(byte port, byte state);

    unsigned int getBootAttempts(byte device);
    void setBootAttempts(byte device, unsigned int attempts);
    void incrementBootAttempts(byte device);

    unsigned int getBootFailures(byte device);
    void setBootFailures(byte device, unsigned int failures);
    void incrementBootFailures(byte device);

    int getFaultCurrent(byte device);
    void setFaultCurrent(byte device, int current);

    unsigned long getFaultTimeout(byte device);
    unsigned long getHeartbeatTimeout(byte device);
    unsigned long getUnmanagedChangeTime(byte device);
    unsigned long getStopTimeout(byte device);

    void logDeviceBootTime(byte device, const time_t &bootTime);
    unsigned long getDeviceBootTime(byte device, byte index);
    byte getDeviceBootTimeCount(byte device);
};

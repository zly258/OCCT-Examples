#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

class PluginInterface {
public:
    virtual ~PluginInterface() {}

    virtual void initialize() = 0;
    virtual void shutdown() = 0;
    virtual const char* getPluginName() const = 0;
    virtual const char* getPluginVersion() const = 0;
};

#endif // PLUGININTERFACE_H
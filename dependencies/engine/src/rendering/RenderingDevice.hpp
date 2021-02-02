#pragma once

class RenderingDeviceInfo;
class ShaderManager;

class RenderingDevice {
public:
    virtual bool init() = 0;

    virtual RenderingDeviceInfo* deviceInfo() = 0;
    virtual ShaderManager* shaderManager() = 0;
};
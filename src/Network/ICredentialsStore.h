//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once

struct WifiCredentials;

class ICredentialsStore {
public:
    virtual ~ICredentialsStore() = default;
    virtual bool load(WifiCredentials& credentials) = 0;
    virtual void save(const WifiCredentials& credentials) = 0;
    virtual void clear() = 0;
};


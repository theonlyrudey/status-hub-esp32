//
// Created by Piotr Rudnicki on 08/05/2026.
//

#pragma once
#include "ICredentialsStore.h"

class PreferencesCredentialsStore : public ICredentialsStore {
public:
    bool load(WifiCredentials& credentials) override;
    void save(const WifiCredentials& credentials) override;
    void clear() override;
};

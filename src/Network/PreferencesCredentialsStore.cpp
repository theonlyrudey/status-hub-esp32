//
// Created by Piotr Rudnicki on 08/05/2026.
//

#include "PreferencesCredentialsStore.h"

#include <cstddef>
#include <cstring>
#include <Preferences.h>
#include <WString.h>

#include "Network/WifiTypes.h"

namespace {
    constexpr char CREDENTIALS_NAMESPACE[] = "wifi_creds";
    static_assert(sizeof(CREDENTIALS_NAMESPACE) - 1 <= 15, "NVS namespace must be <= 15 characters");
    const char* SSID_KEY = "ssid";
    const char* PASSWORD_KEY = "password";

    template <std::size_t N>
    void copyStringToBuffer(const String& source, char (&destination)[N]) {
        static_assert(N > 0, "Buffer size must be greater than 0");
        std::strncpy(destination, source.c_str(), N - 1);
        destination[N - 1] = '\0';
    }
}

bool PreferencesCredentialsStore::load(WifiCredentials &credentials) {
    credentials = WifiCredentials{};

    Preferences preferences;
    const bool beginOk = preferences.begin(CREDENTIALS_NAMESPACE, true);
    if (!beginOk) {
        return false;
    }

    const String ssid = preferences.getString(SSID_KEY, String());
    const String password = preferences.getString(PASSWORD_KEY, String());
    preferences.end();

    copyStringToBuffer(ssid, credentials.ssid);
    copyStringToBuffer(password, credentials.password);

    return !ssid.isEmpty();
}

void PreferencesCredentialsStore::save(const WifiCredentials &credentials) {
    Preferences preferences;
    const bool beginOk = preferences.begin(CREDENTIALS_NAMESPACE, false);
    if (!beginOk) {
        return;
    }

    preferences.putString(SSID_KEY, credentials.ssid);
    preferences.putString(PASSWORD_KEY, credentials.password);
    preferences.end();
}

void PreferencesCredentialsStore::clear() {
    Preferences preferences;
    preferences.begin(CREDENTIALS_NAMESPACE, false);
    preferences.remove(SSID_KEY);
    preferences.remove(PASSWORD_KEY);
    preferences.end();
}

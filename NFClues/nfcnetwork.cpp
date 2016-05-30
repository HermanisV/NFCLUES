#include "nfcnetwork.h"
#include <QString>

NfcNetwork::NfcNetwork()
{

}

QString NfcNetwork::getApiKey()
{
    return g_apiKey;
}

QString NfcNetwork::getUrl()
{
    return g_url;
}

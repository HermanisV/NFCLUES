#ifndef NFCNETWORK_H
#define NFCNETWORK_H
#include <QString>

///
/// \brief The NfcNetwork class
/// Class for all Web transaction related handling
class NfcNetwork
{
public:
    NfcNetwork();
    QString getApiKey();
    QString getUrl();
private:
    const QString g_url = "http://nfclues.northeurope.cloudapp.azure.com/api/v2/nfc_db/_table/";
    const QString g_apiKey = "api_key=82deaa19a6621529a9afe4a8fc5d66d2388d02b8e1745331020e470ece560192";
};

#endif // NFCNETWORK_H

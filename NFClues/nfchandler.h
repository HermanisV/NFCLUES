#ifndef NFCHANDLER_H
#define NFCHANDLER_H

#include <QObject>
#include <QNearFieldManager>
#include <QNdefMessage>
#include <QNdefNfcTextRecord>
#include <QNearFieldShareTarget>
#include <QNearFieldTarget>
#include <QDebug>

/* This class is used for handling all tag related operations
 * writing tag
 * reading tag
 * Handels signals and slots for NFC actions
 */
class NFCHandler : public QObject
{
    Q_OBJECT
public:
    explicit NFCHandler(QObject *parent = 0);
    Q_PROPERTY(int tagId READ tagId WRITE setTagId NOTIFY tagIdChanged)
    Q_PROPERTY(QNdefNfcTextRecord nfcText READ nfcText WRITE setNfcText NOTIFY nfcTextChanged)
    Q_PROPERTY(QNdefMessage nfcMessage READ nfcMessage WRITE setNfcMessage NOTIFY nfcMessageChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorChanged)

    //Getters
    int     tagId();
    QNdefNfcTextRecord nfcText();
    QNdefMessage nfcMessage();
    QString errorString();

    //Setters
    void    setTagId(const int &tagId);
    void    setNfcText(const QNdefNfcTextRecord &nfctext);

    //Methods
    Q_INVOKABLE void startReading();
    Q_INVOKABLE void startWriting();
    Q_INVOKABLE void stopLooking();
    Q_INVOKABLE void addText(QNdefNfcTextRecord textRecord);

signals:
    void tagIdChanged();
    void nfcTextChanged();
    void nfcMessageChanged();
    void gotError(QString);
    void error();
public slots:
    void targetDetected(const QNdefMessage &message, QNearFieldTarget *target);
    void targetLost(QNearFieldTarget *target);
    void targetError(QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id);
protected slots:
    void handleError(QString p_error);
private:
    //Tag data
    int     l_tagId;    
    QString l_message;
    QString l_error;
    QNdefMessage                l_nfcMessage;
    QNdefNfcTextRecord          l_nfcText;


    //
    QNearFieldManager           *l_manager;
    QNearFieldTarget            *l_target;
    QNearFieldTarget::RequestId l_request;

    //states
    enum Action {
        NoAction,
        ReadNdef,
        WriteNdef
    };

    Action  l_action;
};

#endif // NFCHANDLER_H

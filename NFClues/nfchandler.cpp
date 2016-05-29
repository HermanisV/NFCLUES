#include "nfchandler.h"
#include <QObject>
#include <QNearFieldManager>
#include <QNdefMessage>
#include <QNdefNfcTextRecord>
#include <QNearFieldShareTarget>
#include <QNearFieldTarget>
#include <QDebug>

NFCHandler::NFCHandler(QObject *parent) : QObject(parent)
{
    connect(this,SIGNAL(gotError(QString)), this,SLOT(handleError(QString)));
}
//Geters///////////

int NFCHandler::tagId()
{
    return l_tagId;
}

QNdefNfcTextRecord NFCHandler::nfcText()
{
    return l_nfcText;
}

QString NFCHandler::errorString()
{
    return l_error;
}

//Setters/////////////
void NFCHandler::setTagId(const int &tagId)
{
    if (l_tagId == tagId)
        return;
    l_tagId = tagId;
    emit tagIdChanged();
}

void NFCHandler::setNfcText(const QNdefNfcTextRecord &nfctext)
{
    if (nfctext == l_nfcText)
        return;
    l_nfcText = nfctext;
    emit nfcTextChanged();
}
//Methods/////////////
/// \brief NFCHandler::startReading
/// Initiated from QMl to tell backend to start looking for tag to read from
void NFCHandler::startReading()
{
    l_action = ReadNdef;
    l_manager->setTargetAccessModes(QNearFieldManager::NdefReadTargetAccess);
    l_manager->startTargetDetection();
}
/// \brief NFCHandler::startWriting
/// Initiated from QMl to tell backend to stop looking for tags to write in
void NFCHandler::startWriting()
{
    l_action = WriteNdef;
    l_manager->setTargetAccessModes(QNearFieldManager::NdefWriteTargetAccess);
    l_manager->startTargetDetection();
}
//Slots////////////////
/// \brief NFCHandler::targetDetected
/// Slot called form QNearFieldManager when a tag hs been detected
/// \param message - filled with a message if it's returned from manager
/// \param target - target tag that is detected
void NFCHandler::targetDetected(const QNdefMessage &message, QNearFieldTarget *target)
{
    switch (l_action) {
    case NoAction:
        break;
    case WriteNdef:
        connect(target, SIGNAL(error(QNearFieldTarget::Error,QNearFieldTarget::RequestId)),
                this, SLOT(targetError(QNearFieldTarget::Error,QNearFieldTarget::RequestId)));
        connect(target, SIGNAL(ndefMessagesWritten()), this, SLOT(ndefMessageWritten()));

        l_request = target->writeNdefMessages(QList<QNdefMessage>() << l_nfcMessage);
        if (!l_request.isValid()) // cannot write messages
            targetError(QNearFieldTarget::NdefWriteError, l_request);
        break;
    case ReadNdef:
        connect(target, SIGNAL(error(QNearFieldTarget::Error,QNearFieldTarget::RequestId)),
                this, SLOT(targetError(QNearFieldTarget::Error,QNearFieldTarget::RequestId)));
        connect(target, SIGNAL(ndefMessageRead(QNdefMessage)),
                this, SLOT(ndefMessageRead(QNdefMessage)));

        l_request = target->readNdefMessages();
        if (!l_request.isValid()) // cannot read messages
            targetError(QNearFieldTarget::NdefReadError, l_request);
        break;
    }
}

void NFCHandler::targetLost(QNearFieldTarget *target)
{
    target->deleteLater();
}

void NFCHandler::targetError(QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id)
{
    if (l_request == id) {
        switch (error) {
        case QNearFieldTarget::NoError:
            qDebug()<<"No error";
            break;
        case QNearFieldTarget::UnsupportedError:
            gotError("Sorry, Unsupported tag");
            break;
        case QNearFieldTarget::TargetOutOfRangeError:
            gotError("Tag has been removed from the field");
            break;
        case QNearFieldTarget::NoResponseError:
            gotError("No response from the tag");
            break;
        case QNearFieldTarget::ChecksumMismatchError:
            qDebug()<<"Checksum mismatch";
            gotError("Ooops, there seems to be a problem");
            break;
        case QNearFieldTarget::InvalidParametersError:
            qDebug()<<"Invalid parameters";
            gotError("Ooops, there seems to be a problem");
            break;
        case QNearFieldTarget::NdefReadError:
            qDebug()<<"NDEF read error";
            gotError("Ooops, there seems to be a problem");
            break;
        case QNearFieldTarget::NdefWriteError:
            qDebug()<<"NDEF write error";
            gotError("Ooops, there seems to be a problem");
            break;
        default:
            gotError("Ooops, there seems to be a problem");
        }

        l_manager->setTargetAccessModes(QNearFieldManager::NoTargetAccess);
        l_manager->stopTargetDetection();
        l_request = QNearFieldTarget::RequestId();
    }
}

void NFCHandler::handleError(QString p_error)
{
    qDebug() << "Error happened";
    if (p_error == l_error)
    {
        return;
    }
    else
    {
        l_error = p_error;
        emit error();
    }
}

void NFCHandler::stopLooking()
{
    l_manager->stopTargetDetection();
}

void NFCHandler::addText(QNdefNfcTextRecord textRecord)
{
    l_nfcMessage.append(l_nfcText);
}



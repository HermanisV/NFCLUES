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
    l_manager = new QNearFieldManager(this);
    connect(l_manager,SIGNAL(targetDetected(QNearFieldTarget*)),
            this,SLOT(targetDetected(QNearFieldTarget*)));
    connect(l_manager,SIGNAL(targetLost(QNearFieldTarget*)),
            this,SLOT(targetLost(QNearFieldTarget*)));
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

QNdefMessage NFCHandler::nfcMessage()
{
    return l_nfcMessage;
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

void NFCHandler::setNfcMessage(const QNdefMessage &nfcMessage)
{
    if (nfcMessage == l_nfcMessage)
        return;
    l_nfcMessage = nfcMessage;
    emit nfcMessageChanged();
}
//Methods/////////////
/// \brief NFCHandler::startReading
/// Initiated from QMl to tell backend to start looking for tag to read from
void NFCHandler::startReading()
{
    l_action = ReadNdef;
    l_manager->setTargetAccessModes(QNearFieldManager::NdefReadTargetAccess);
    l_manager->startTargetDetection();
    emit startedLooking();
}
/// \brief NFCHandler::startWriting
/// Initiated from QMl to tell backend to stop looking for tags to write in
void NFCHandler::startWriting()
{

    qDebug()<<"In NFCHandler::startWriting";
    l_action = WriteNdef;
    l_manager->setTargetAccessModes(QNearFieldManager::NdefWriteTargetAccess);
    qDebug()<<"Access mode set, starting detection";
    emit startedLooking();
    l_manager->startTargetDetection();
}
//Slots////////////////
/// \brief NFCHandler::targetDetected
/// Slot called form QNearFieldManager when a tag has been detected
/// \param message - filled with a message if it's returned from manager
/// \param target - target tag that is detected
void NFCHandler::targetDetected(QNearFieldTarget *target)
{

    qDebug()<<"NFCHandler::targetDetected";
    emit foundTarget();
    switch (l_action) {
    case NoAction:
        break;
    case WriteNdef:
        qDebug()<<"Write tag";
        connect(target, SIGNAL(ndefMessagesWritten()), this, SLOT(ndefMessageWritten()));
        connect(target, SIGNAL(error(QNearFieldTarget::Error,QNearFieldTarget::RequestId)),
                this, SLOT(targetError(QNearFieldTarget::Error,QNearFieldTarget::RequestId)));
        if (target->hasNdefMessage()) //This is getting commented out for easier
        {
            gotError("Tag already filled");
        }
        else
        {
            l_request = target->writeNdefMessages(QList<QNdefMessage>() << l_nfcMessage);
            if (!l_request.isValid()) // cannot write messages
                targetError(QNearFieldTarget::NdefWriteError, l_request);
        }
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
///
/// \brief NFCHandler::targetLost
/// A slot called from QNearFieldManager when a target has been lost
/// \param target - pointer to the lost target
void NFCHandler::targetLost(QNearFieldTarget *target)
{
    target->deleteLater();
}
///
/// \brief NFCHandler::targetError
/// Slot called from targetDetected if an error has occured during NFC transaction
/// \param error - the type of error
/// \param id - the NFc request that failed
///
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

void NFCHandler::ndefMessageWritten()
{
    l_manager ->setTargetAccessModes(QNearFieldManager::NoTargetAccess);
    l_manager ->stopTargetDetection();
    emit tagWritten();
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
        l_manager ->setTargetAccessModes(QNearFieldManager::NoTargetAccess);
        l_manager ->stopTargetDetection();
        emit error();
    }
}

void NFCHandler::stopLooking()
{
    l_manager->stopTargetDetection();
}
///
/// \brief NFCHandler::addText
/// Used to add text type record to the message being written in a tag
/// \param textRecord - The record that should be added to the message
///
void NFCHandler::addText(QString text)
{
    qDebug()<<"In NFCHandler::addText";
    if (text== NULL || text.length() != 7)
        gotError("Wrong Tag Id");
    l_nfcText.setText("This adventures Code: " + text);
    l_nfcText.setLocale("EN");
    qDebug()<<"Text OK, appending to message";
    l_nfcMessage.append(l_nfcText);
    emit tagTextOk();
}



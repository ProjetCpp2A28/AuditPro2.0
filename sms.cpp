#include <QtNetwork>
#include "sms.h"


QString twilio_phone_number = "+12565677501"; //numero from where you get the sms


sms::sms(){

}
void sms::sendSMS(const QString &to, const QString &message) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QUrl url("https://api.twilio.com/2010-04-01/Accounts/ACe5f356d6a4efad791ff0d977af95820d/Messages.json"); // lien site de l api _servie message ( twilio )
    QNetworkRequest request(url);


    QString credentials = "ACe5f356d6a4efad791ff0d977af95820d:99c616ade6f43cb699bf46a11942bf42";    // partie 1 = SID partie 2 = token
    QByteArray base64Credentials = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + base64Credentials);


    QByteArray postData;
    postData.append("From="+twilio_phone_number.toUtf8());  // from wherre i get the sms
    postData.append("&To=" + to.toUtf8()); // to who i send the sms
    postData.append("&Body=" + message.toUtf8()); // sms message


    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Make the request
    QNetworkReply *reply = manager->post(request, postData);


    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {//test si il ya un error
            qDebug() << "SMS sent successfully";
        } else {
            qDebug() << "Failed to send SMS:" << reply->errorString();
        }


        reply->deleteLater();
        manager->deleteLater();
    });
}

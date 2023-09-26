#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{

    serviceUdpSocket = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);

    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);

}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram) {
    QByteArray data = datagram.data();
    QString senderAddress = datagram.senderAddress().toString();
    int messageSize = data.size();

    // Отправляем сигнал с данными в интерфейс
    emit sig_sendReceivedData(senderAddress, messageSize);

    // Добавьте здесь код для обработки полученных данных, если это необходимо.
}

/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
            ReadDatagram(datagram);
    }

}

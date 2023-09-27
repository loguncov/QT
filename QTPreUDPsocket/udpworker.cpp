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
 * @param datagram - принятая датаграмма
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram) {
    // Извлекаем данные из датаграммы
    QByteArray data = datagram.data();

    // Извлекаем адрес отправителя
    QString senderAddress = datagram.senderAddress().toString();

    // Вычисляем размер сообщения
    int messageSize = data.size();

    // Отправляем сигнал с полученными данными (адрес отправителя и размер сообщения) в интерфейс
    emit sig_sendReceivedData(senderAddress, messageSize);

    // Добавьте здесь код для дополнительной обработки полученных данных, если это необходимо.

    // Извлекаем и декодируем время из данных датаграммы
    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime dateTime;
    inStr >> dateTime;

    // Отправляем извлеченное время в интерфейс
    emit sig_sendTimeToGUI(dateTime);
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

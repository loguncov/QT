#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Инициализация модуля сети
    QNetworkAccessManager networkManager;
    QNetworkRequest request(QUrl("https://www.example.com"));
    QNetworkReply *reply = networkManager.get(request);

    // Обработчик завершения запроса
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        QString result;
        if (reply->error() == QNetworkReply::NoError) {
            result = "HTTP-запрос выполнен успешно!";
            QByteArray data = reply->readAll();
            // Используйте данные ответа здесь
        } else {
            result = "Ошибка HTTP-запроса: " + reply->errorString();
        }

        // Инициализация модуля базы данных
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("mydatabase.db");

        // Подключение к базе данных
        if (!database.open()) {
            qDebug() << "Ошибка подключения к базе данных!";
            return;
        }

        // Создание таблицы, если не существует
        QSqlQuery query;
        if (!query.exec("CREATE TABLE IF NOT EXISTS requests (id INTEGER PRIMARY KEY AUTOINCREMENT, result TEXT, datetime DATETIME)")) {
            qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
            return;
        }

        // Подготовка запроса на вставку данных
        query.prepare("INSERT INTO requests (result, datetime) VALUES (?, ?)");
        query.addBindValue(result);
        query.addBindValue(QDateTime::currentDateTime());

        // Выполнение запроса на вставку
        if (!query.exec()) {
            qDebug() << "Ошибка вставки данных:" << query.lastError().text();
            return;
        }

        // Вывод базы данных в виде таблицы
        QSqlQuery selectQuery("SELECT * FROM requests");
        qDebug() << "ID | Результат запроса | Дата и время";
        while (selectQuery.next()) {
            qDebug() << selectQuery.value(0).toInt() << " | " << selectQuery.value(1).toString() << " | " << selectQuery.value(2).toDateTime().toString();
        }

        reply->deleteLater();
    });

    return a.exec();
}

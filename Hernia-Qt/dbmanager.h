
#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>


class DbManager
{
public:
    DbManager(const QString& path);
    ~DbManager();

    bool isOpen() const;
    bool removePerson(const QString& name);
    bool personExists(const QString& name) const;
    bool addSurgeon(const QString& name);
    QSqlQueryModel* Load_Surgeons();

    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

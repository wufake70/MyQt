#ifndef MODELEXTEND_H
#define MODELEXTEND_H

#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>
#include <QMap>
#include <QVariant>

class ModelExtend: public QAbstractTableModel
{
    Q_OBJECT
    QVector<short> id_index_vec;
    QVector<short> name_index_vec;

    QMap<short,QString> id_map;
    QMap<short,QString> name_map;

    // 表头
    QStringList header_strlist;

    void InitTableHeaders();

protected:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const;
public:
    explicit ModelExtend(QObject *parent=0);
//    virtual ~ModelExtend();

};

#endif // MODELEXTEND_H

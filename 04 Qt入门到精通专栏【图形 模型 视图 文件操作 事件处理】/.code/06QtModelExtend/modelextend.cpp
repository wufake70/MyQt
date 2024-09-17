#include "modelextend.h"

ModelExtend::ModelExtend(QObject *parent)
    :    QAbstractTableModel(parent)
{
    for(int i=1;i<=5;i++)
    {
        id_map[i] = QString("202400%1").arg(i);
    }
    name_map[1]="张三1";
    name_map[2]="张三2";
    name_map[3]="张三3";
    name_map[4]="张三4";
    name_map[5]="张三5";

    InitTableHeaders();


}

void ModelExtend::InitTableHeaders()
{
    header_strlist << "id" << "name";
    id_index_vec << 1 << 2 << 3 << 4 << 5;
    name_index_vec << 1 << 2 << 3 << 4 << 5;

}


int ModelExtend::rowCount(const QModelIndex &parent ) const
{
    return id_index_vec.size();
}
int ModelExtend::columnCount(const QModelIndex &parent) const
{
    return header_strlist.size();
}
QVariant ModelExtend::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role==Qt::DisplayRole)
    {
        switch (index.column()) {
        case 0:
            return id_map[id_index_vec[index.row()]];
        case 1:
            return name_map[name_index_vec[index.row()]];
        default:
            return QVariant();

        }
    }
    return QVariant();
}
QVariant ModelExtend::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if(role=Qt::DisplayRole&&orientation==Qt::Horizontal)
        return header_strlist[section];

    return QAbstractTableModel::headerData(section,orientation,role);
}

//ModelExtend::~ModelExtend()
//{

//}

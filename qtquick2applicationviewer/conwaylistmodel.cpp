#include "conwaylistmodel.h"

ConwayListModel::ConwayListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_universe = new bool[(m_universeSize + 2) * (m_universeSize + 2)];
    m_next = new bool[(m_universeSize + 2) * (m_universeSize + 2)];

    memset(m_universe, false, sizeof(bool)*(m_universeSize + 2) * (m_universeSize + 2));
    memset(m_next, false, sizeof(bool)*(m_universeSize + 2) * (m_universeSize + 2));
}

ConwayListModel::~ConwayListModel()
{
    delete []m_universe;
    delete []m_next;
}

int ConwayListModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant ConwayListModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

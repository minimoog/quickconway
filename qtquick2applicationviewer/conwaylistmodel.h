#ifndef CONWAYLISTMODEL_H
#define CONWAYLISTMODEL_H

#include <QAbstractListModel>

class ConwayListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ConwayListModel(QObject *parent = 0);
    ~ConwayListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

signals:

public slots:

private:
    bool isAlive(int k, int j);

    bool *m_universe;
    bool *m_next;
    int m_universeSize;
};

#endif // CONWAYLISTMODEL_H

/*
 * Copyright (c) 2013 Antonie Jovanoski <minimoog77_at_gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "conwaylistmodel.h"

ConwayListModel::ConwayListModel(QObject *parent) :
    QAbstractListModel(parent),
    m_universeSize(50),
    m_universe((m_universeSize + 2) * (m_universeSize + 2), false),
    m_nextUniverse((m_universeSize + 2) * (m_universeSize + 2), false)
{
}

ConwayListModel::~ConwayListModel()
{
}

int ConwayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_universeSize * m_universeSize;
}

QVariant ConwayListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= (m_universeSize * m_universeSize)) {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
        return m_universe[index.row() + m_universeSize * 1 + 1];

    return QVariant();
}

bool ConwayListModel::isAlive(int k, int j)
{
    int power = 0;
    power += m_universe[(k + 1) * m_universeSize + j];
    power += m_universe[(k - 1) * m_universeSize + j];
    power += m_universe[k * m_universeSize + (j + 1)];
    power += m_universe[k * m_universeSize + (j - 1)];
    power += m_universe[(k + 1) * m_universeSize + (j - 1)];
    power += m_universe[(k - 1) * m_universeSize + (j + 1)];
    power += m_universe[(k - 1) * m_universeSize + (j - 1)];
    power += m_universe[(k + 1) * m_universeSize + (j + 1)];

    if (((m_universe[k * m_universeSize + j] == true) && (power == 2)) || (power == 3))
        return true;

    return false;
}

int ConwayListModel::universeSize() const
{
    return m_universeSize;
}

void ConwayListModel::setUniverseSize(int universeSize)
{
    if (m_universeSize != universeSize) {
        m_universeSize = universeSize;

        beginResetModel();

        m_universe.clear();
        m_nextUniverse.clear();

        for (int i = 0; i < (m_universeSize + 2) * (m_universeSize + 2); ++i) {
            m_universe.push_back(false);
            m_nextUniverse.push_back(false);
        }

        endResetModel();

        emit universeSizeChanged();
    }
}

void ConwayListModel::nextGeneration()
{
    for(int k = 1; k <= m_universeSize; k++) {
        for(int j = 1; j <= m_universeSize; j++) {
            m_nextUniverse[k * m_universeSize + j] = isAlive(k, j);
        }
    }

    for(int k = 1; k <= m_universeSize; k++) {
        for(int j = 1; j <= m_universeSize; j++) {
            if (m_universe[k * m_universeSize + j] != m_nextUniverse[k * m_universeSize + j]) {
                QModelIndex indexChanged= createIndex((k - 1) * m_universeSize + (j - 1), 0);

                m_universe[k * m_universeSize + j] = m_nextUniverse[k * m_universeSize + j];

                emit dataChanged(indexChanged, indexChanged);
            }
        }
    }
}

void ConwayListModel::randomize()
{
    beginResetModel();

    for(int k = 1; k <= m_universeSize; k++) {
        for(int j = 1; j <= m_universeSize; j++) {
            m_universe[k * m_universeSize + j] = qrand() % 2;
        }
    }

    endResetModel();
}

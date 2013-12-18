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

import QtQuick 2.2
import com.minimoog77 1.0

Rectangle {
    width: 500
    height: 500

    Component {
        id: cellDelegate

        Rectangle {
            width: GridView.view.cellWidth
            height: GridView.view.cellHeight
            color: display ? "black" : "white"
        }
    }

    GridView {
        id: conwayView

        cellHeight: parent.height / 50;
        cellWidth: parent.width / 50;
        anchors.fill: parent

        delegate: cellDelegate

        model: conwayListModel
    }

    ConwayListModel {
        id: conwayListModel
    }

    Component.onCompleted: {
        conwayListModel.randomize();
    }

    Timer {
        interval: 500
        repeat: true;
        running: true;
        triggeredOnStart: false

        onTriggered: {
            conwayListModel.nextGeneration()
        }
    }
}

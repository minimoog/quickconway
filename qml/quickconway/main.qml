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
    id: root

    width: 500
    height: 500

    Grid {
        id: gridView

        columns: conwayListModel.universeSize
        rows: conwayListModel.universeSize
        anchors.fill: parent

        Repeater {
            model: conwayListModel

            ShaderEffect {
                width: gridView.width / conwayListModel.universeSize
                height: gridView.height / conwayListModel.universeSize
                property real blackorwhite: display ? 0 : 1

                vertexShader: "
                    uniform highp mat4 qt_Matrix;
                    attribute highp vec4 qt_Vertex;

                    void main()
                    {
                        gl_Position = qt_Matrix * qt_Vertex;
                    }"

                fragmentShader: "
                    uniform lowp float blackorwhite;

                    void main()
                    {
                        gl_FragColor = vec4(vec3(blackorwhite), 1.0);
                    }
                    "
            }
        }
    }

    ConwayListModel {
        id: conwayListModel
    }

    Component.onCompleted: {
        conwayListModel.randomize();
    }

    Timer {
        interval: 100
        repeat: true;
        running: true;
        triggeredOnStart: false

        onTriggered: {
            conwayListModel.nextGeneration()
        }
    }
}

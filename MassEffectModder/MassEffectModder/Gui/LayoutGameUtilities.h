/*
 * MassEffectModder
 *
 * Copyright (C) 2019 Pawel Kolodziejski
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef LAYOUT_GAME_UTILITIES_H
#define LAYOUT_GAME_UTILITIES_H

class MainWindow;

class LayoutGameUtilities: public QWidget
{
    Q_OBJECT

public:
    explicit LayoutGameUtilities(QWidget *parent = nullptr,
                                 QStackedLayout *layout = nullptr,
                                 MainWindow *window = nullptr);

private slots:
    void CheckGameFilesSelected();
    void ChangeGamePathSelected();
    void RepackGameFilesSelected();
    void UpdateTOCsSelected();
    void ExtractDLCsSelected();
    void ReturnSelected();

private:
    const int kButtonMinWidth = 300;
    const int kButtonMinHeight = 100;
#if defined(__APPLE__)
    const int kFontSize = 20;
#elif defined(__linux__)
    const int kFontSize = 13;
#else
    const int kFontSize = 15;
#endif

    QStackedLayout *stackedLayout;
    MainWindow *mainWindow;
};

#endif // LAYOUT_GAME_UTILITIES_H
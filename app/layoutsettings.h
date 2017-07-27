/*
*  Copyright 2017  Smith AR <audoban@openmailbox.org>
*                  Michail Vourlakos <mvourlakos@gmail.com>
*
*  This file is part of Latte-Dock
*
*  Latte-Dock is free software; you can redistribute it and/or
*  modify it under the terms of the GNU General Public License as
*  published by the Free Software Foundation; either version 2 of
*  the License, or (at your option) any later version.
*
*  Latte-Dock is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LAYOUTSETTINGS_H
#define LAYOUTSETTINGS_H

#include <QObject>

#include <KConfigGroup>
#include <KSharedConfig>

#include "dockcorona.h"

class DockCorona;

namespace Latte {

//! This class is responsible to hold the settings for a specific layout.
//! It also updates always the relevant layout configuration concerning
//! its general settings (no the containments)
class LayoutSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool showInMenu READ showInMenu WRITE setShowInMenu NOTIFY showInMenuChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QStringList launchers READ launchers WRITE setLaunchers NOTIFY launchersChanged)
    Q_PROPERTY(QStringList activities READ activities WRITE setActivities NOTIFY activitiesChanged)

public:
    LayoutSettings(QObject *parent, QString layoutFile, QString layoutName = QString());
    ~LayoutSettings() override;

    bool showInMenu() const;
    void setShowInMenu(bool show);

    bool fileIsBroken() const;

    int version() const;
    void setVersion(int ver);

    QString name() const;
    QString file() const;

    QString color() const;
    void setColor(QString color);

    QStringList activities() const;
    void setActivities(QStringList activities);

    QStringList launchers() const;
    void setLaunchers(QStringList launcherList);

    static QString layoutName(const QString &fileName);

signals:
    void activitiesChanged();
    void colorChanged();
    void fileChanged();
    void launchersChanged();
    void nameChanged();
    void versionChanged();
    void showInMenuChanged();

private slots:
    void loadConfig();
    void saveConfig();

private:
    void init();
    void setName(QString name);
    void setFile(QString file);

private:
    bool m_showInMenu{false};
    //if version doesnt exist it is and old layout file
    int m_version{2};

    QString m_color;
    QString m_layoutFile;
    QString m_layoutName;
    QStringList m_activities;
    QStringList m_launchers;

    DockCorona *m_corona{nullptr};
    KConfigGroup m_layoutGroup;
};

}

#endif // LAYOUTSETTINGS_H

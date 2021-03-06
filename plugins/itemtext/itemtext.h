/*
    Copyright (c) 2014, Lukas Holecek <hluk@email.cz>

    This file is part of CopyQ.

    CopyQ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CopyQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CopyQ.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ITEMTEXT_H
#define ITEMTEXT_H

#include "gui/icons.h"
#include "item/itemwidget.h"

#include <QTextDocument>
#include <QTextBrowser>

#include <memory>

namespace Ui {
class ItemTextSettings;
}

class ItemText : public QTextBrowser, public ItemWidget
{
    Q_OBJECT

public:
    ItemText(const QString &text, bool isRichText, int maxLines, int maximumHeight, QWidget *parent);

protected:
    void highlight(const QRegExp &re, const QFont &highlightFont,
                           const QPalette &highlightPalette) override;

    void updateSize(const QSize &maximumSize, int idealWidth) override;

    bool eventFilter(QObject *, QEvent *event) override;

private:
    QTextDocument m_textDocument;
    int m_maximumHeight;
};

class ItemTextLoader : public QObject, public ItemLoaderInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID COPYQ_PLUGIN_ITEM_LOADER_ID)
    Q_INTERFACES(ItemLoaderInterface)

public:
    ItemTextLoader();
    ~ItemTextLoader();

    ItemWidget *create(const QModelIndex &index, QWidget *parent, bool preview) const override;

    QString id() const override { return "itemtext"; }
    QString name() const override { return tr("Text"); }
    QString author() const override { return QString(); }
    QString description() const override { return tr("Display plain text and simple HTML items."); }
    QVariant icon() const override { return QVariant(IconFont); }

    QStringList formatsToSave() const override;

    QVariantMap applySettings() override;

    void loadSettings(const QVariantMap &settings) override { m_settings = settings; }

    QWidget *createSettingsWidget(QWidget *parent) override;

private:
    QVariantMap m_settings;
    std::unique_ptr<Ui::ItemTextSettings> ui;
};

#endif // ITEMTEXT_H

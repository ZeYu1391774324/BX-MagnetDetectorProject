#ifndef MULTISELECTCOMBOBOX_H
#define MULTISELECTCOMBOBOX_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QComboBox>
class MultiSelectComboBox : public QComboBox
{
    Q_OBJECT

public:
    MultiSelectComboBox(QWidget *parent = nullptr);
    ~MultiSelectComboBox() override;
    void addItem(const QString &text, const QVariant &userData = QVariant());
    void addItem(const QIcon &icon, const QString &text, const QVariant &userData = QVariant());
    void addItems(const QStringList &texts);
    void sellectAll();
    QStringList currentText();
    QList<int> currentIndex();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void showPopup() override;
    void hidePopup() override;
private:
    bool isPermitHidePopup;
    QListView* selectItemView;
    QStandardItemModel* selectModel;
    QListView* popupView;
    QStandardItemModel* popupModel;
    void selectItemViewPress(QPoint pos);


};

#endif // MULTISELECTCOMBOBOX_H

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

class Dialog : public QDialog {
    Q_OBJECT

public:
    Dialog( QWidget* parent = 0 );
    ~Dialog();

    QString getInput() const;

signals:
    void applied();

private:
    QLineEdit* m_edit;
};


#endif

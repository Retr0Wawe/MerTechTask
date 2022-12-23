#include "gui/dialog.hpp"

Dialog::Dialog( QWidget* parent ) : QDialog( parent ) {

}

Dialog::~Dialog() {
}

QString Dialog::getInput() const {
    return m_edit->text();
}

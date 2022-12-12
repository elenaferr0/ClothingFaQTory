#include <QVBoxLayout>
#include "product_tab_page.h"
#include "../spoiler.h"

ProductTabPage::ProductTabPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(new QLabel("labl"));

}

#include <QToolButton>
#include "materials_view.h"

using Views::MaterialsView;

int MaterialsView::COLUMN_COUNT = 4;

MaterialsView::MaterialsView(QWidget* parent) : ObserverWidget(parent), materials(MaterialsList()) {}

void MaterialsView::init(const MaterialsList& materials) {
    this->materials = materials;
    gridLayout = new QGridLayout(this);
    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSpacing(60);

    initGrid();
}

void Views::MaterialsView::initGrid() {

    int row = 0, col = 0;

    for (auto material: materials) {
        QToolButton * button = new QToolButton();
        string materialName = material->getNameAsString();

        QString capitalizedName = QString::fromStdString(materialName).at(0).toUpper() +
                                  QString::fromStdString(materialName.substr(1, materialName.size() - 1)).toLower();

        QString text = capitalizedName + "\n"
                       + QString::number(material->getCostPerUnit(), 'f', 2) + "$/" +
                       QString::fromStdString(material->getUnitOfMeasureAsString());

        button->setText(text);
        button->setIcon(QIcon(":/assets/icons/" + QString::fromStdString(materialName).toLower() + ".png"));
        button->setIconSize(QSize(50, 50));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setObjectName("materialButton"); // for stylesheet

        gridLayout->addWidget(button, row, col);

        col++;
        if (col == COLUMN_COUNT) {
            row++;
            col = 0;
        }
    }

}

void Views::MaterialsView::notify(Model* model) {
    // TODO: handle notify event
}

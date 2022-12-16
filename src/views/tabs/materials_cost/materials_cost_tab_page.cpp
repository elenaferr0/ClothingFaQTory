#include <QLabel>
#include <QToolButton>
#include <string>
#include "materials_cost_tab_page.h"

int MaterialsCostTabPage::COLUMN_COUNT = 4;

MaterialsCostTabPage::MaterialsCostTabPage(QWidget* parent)
        : QWidget(parent), materialRepository(MaterialRepository::getInstance()) {


    gridLayout = new QGridLayout(this);
    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSpacing(60);
    createGrid();
}


void MaterialsCostTabPage::updateGrid() {

}

void MaterialsCostTabPage::createGrid() {
    Either<Error, list<Material>> materialsOrError = materialRepository->findAll();

    int row = 0, col = 0;
    if (materialsOrError.isRight()) {
        list<Material> materials = materialsOrError.forceRight();

        for (auto material: materials) {
            QToolButton* button = new QToolButton();
            string materialName = material.getNameAsString();

            QString capitalizedName = QString::fromStdString(materialName).at(0).toUpper() +
                                      QString::fromStdString(materialName.substr(1, materialName.size() - 1)).toLower();

            QString text = capitalizedName + "\n"
                           + QString::number(material.getCostPerUnit(), 'f', 2) + "$/" +
                           QString::fromStdString(material.getUnitOfMeasureAsString());

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
}



#ifndef SEARCH_VIEW_H
#define SEARCH_VIEW_H

#include "widget_view_parent.h"
#include "main_view.h"
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleValidator>
#include "../core/filters/filter.h"

using Core::Filter;
namespace Views {
    class MainView;

    class SearchDialog : public QDialog {
        Q_OBJECT
        private:
            QDoubleValidator* maxValidator;

            QGroupBox* productTypeGroupBox;
            QGroupBox* codeGroupBox;
            QGroupBox* priceRangeGroupBox;
            QLineEdit* minPriceLineEdit;
            QLineEdit* maxPriceLineEdit;
            QGroupBox* sortGroupBox;

            QPushButton* searchButton;
            QLineEdit* codeLineEdit;
            LinkedList<QCheckBox*> productTypeCheckboxes;

            QLabel* productTypeError;
            QLabel* codeError;
            QLabel* priceError;

        public:
            SearchDialog(QWidget* parent = nullptr);

        signals:

            void searchStarted(Filter);

        private slots:

            void handleMinPriceTextChanged(const QString& price);

            void handleLineEditChanged(const QString& price);

            void validate();
    };
}

#endif //SEARCH_VIEW_H

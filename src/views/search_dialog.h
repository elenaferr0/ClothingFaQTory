

#ifndef SEARCH_VIEW_H
#define SEARCH_VIEW_H

#include "widget_view_parent.h"
#include "main_view.h"
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleValidator>
#include "../core/filters.h"

using Core::Filters;
namespace Views {
    class MainView;

    class SearchDialog : public QDialog {
        Q_OBJECT
        private:
            static QVector<QString> sortableFields;
            QDoubleValidator* maxValidator;

            QGroupBox* productTypeGroupBox;
            QGroupBox* codeGroupBox;
            QGroupBox* priceRangeGroupBox;
            QLineEdit* minPriceLineEdit;
            QLineEdit* maxPriceLineEdit;
            QGroupBox* sortGroupBox;
            QComboBox* sortFieldComboBox;
            QComboBox* orderComboBox;

            QPushButton* searchButton;
            QLineEdit* codeLineEdit;
            LinkedList<QCheckBox*> productTypeCheckboxes;

            QLabel* productTypeError;
            QLabel* codeError;
            QLabel* priceError;

        public:
            static const int MAX_PRICE;
            SearchDialog(QWidget* parent = nullptr);

        signals:

            void startSearch(Filters filters);

        private slots:

            void handleMinPriceTextChanged(const QString& price);

            void handleLineEditChanged(const QString& price);

            void validate();

            void completed();
    };
}

#endif //SEARCH_VIEW_H

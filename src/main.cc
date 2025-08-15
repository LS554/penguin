// Copyright (c) 2025, London Sheard
// Licensed under the 3-Clause Sheard License                                                                               
// See the LICENSE file in project root for details. 

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QClipboard>
#include <QMessageBox>
#include <QLineEdit>

#include "gen.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Penguin Password Generator");
    window.resize(500, 100);

    QVBoxLayout layout(&window);


    QLabel* passLabel = new QLabel("\n");
    passLabel->hide();
    layout.addWidget(passLabel);

    QLabel* blankLabel = new QLabel("\n");
    blankLabel->hide();
    layout.addWidget(passLabel);

    QLabel* lenLabel = new QLabel("Password length:");
    layout.addWidget(lenLabel);

    QLineEdit* textbox = new QLineEdit();
    textbox->setMaxLength(2);
    textbox->setMinimumWidth(25);
    textbox->setMaximumWidth(25);
    layout.addWidget(textbox);

    QPushButton* genButton = new QPushButton("Generate password");
    layout.addWidget(genButton);

    QPushButton* copyButton = new QPushButton("Copy to clipboard");
    copyButton->hide();
    layout.addWidget(copyButton);

    QObject::connect(genButton, &QPushButton::clicked, [passLabel,textbox, copyButton]() -> void {
	QString text = textbox->text();
	bool ok;
	int len = text.toInt(&ok);
	if (!ok) {
	    QMessageBox::critical(nullptr, "Error", "Please enter a valid length");
	    textbox->setText("");
	    return;
	}
        std::string password = GenPassword(static_cast<size_t>(len));
        passLabel->setText(QString::fromStdString(password));
        passLabel->show();
	copyButton->show();
	return;
    });

    QObject::connect(copyButton, &QPushButton::clicked, [passLabel](){
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(passLabel->text());
    });

    window.show();
    return app.exec();
}

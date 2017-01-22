// main.cpp

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QtWidgets>
#include "MaFenetre.h"
#include "FenPrincipale.h"
#include "FenPrincipale2.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    MaFenetre fenetre;*/

    /*QWidget fenetre;

    // Création du layout de formulaire et de ses widgets

    QLineEdit *nom = new QLineEdit;
    QLineEdit *prenom = new QLineEdit;
    QLineEdit *age = new QLineEdit;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Votre &nom", nom);
    formLayout->addRow("Votre &prénom", prenom);
    formLayout->addRow("Votre â&ge", age);

    // Création du layout principal de la fenêtre (vertical)

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(formLayout); // Ajout du layout de formulaire

    QPushButton *boutonQuitter = new QPushButton("Quitter");
    QWidget::connect(boutonQuitter, SIGNAL(clicked()), &app, SLOT(quit()));
    layoutPrincipal->addWidget(boutonQuitter); // Ajout du bouton

    fenetre.setLayout(layoutPrincipal);*/


    /*QWidget fenetre;

        QPushButton *bouton = new QPushButton("Ouvrir la fenêtre", &fenetre);

        //QCheckBox *checkbox = new QCheckBox("J'aime les frites", &fenetre);

        QGroupBox *groupbox = new QGroupBox("Votre plat préféré", &fenetre);

            QRadioButton *steacks = new QRadioButton("Les steacks");
            QRadioButton *hamburgers = new QRadioButton("Les hamburgers");
            QRadioButton *nuggets = new QRadioButton("Les nuggets");

            steacks->setChecked(true);

            QVBoxLayout *vbox = new QVBoxLayout;
            vbox->addWidget(steacks);
            vbox->addWidget(hamburgers);
            vbox->addWidget(nuggets);

            groupbox->setLayout(vbox);
            groupbox->move(20, 35);

        QComboBox *liste = new QComboBox(&fenetre);
            liste->addItem("Paris");
            liste->addItem("Londres");
            liste->addItem("Singapour");
            liste->addItem("Tokyo");
            liste->move(150,5);

    QDialog secondeFenetre (&fenetre);
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel(&secondeFenetre);
        image->setPixmap(QPixmap("img/smile.png"));
        layout->addWidget(image);
        secondeFenetre.setLayout(layout);

    QWidget::connect(bouton, SIGNAL(clicked()), &secondeFenetre, SLOT(exec()));


        // 1 : Créer le QTabWidget
        QTabWidget *onglets = new QTabWidget(&fenetre);
        onglets->setGeometry(30, 20, 240, 160);
        onglets->move(5,300);

        // 2 : Créer les pages, en utilisant un widget parent pour contenir chacune des pages
        QWidget *page1 = new QWidget;
        QWidget *page2 = new QWidget;
        QLabel *page3 = new QLabel; // Comme un QLabel est aussi un QWidget (il en hérite), on peut aussi s'en servir de page

        // 3 : Créer le contenu des pages de widgets

            // Page 1

            QLineEdit *lineEdit = new QLineEdit("Entrez votre nom");
            QPushButton *bouton1 = new QPushButton("Cliquez ici");
            QPushButton *bouton2 = new QPushButton("Ou là…");

            QVBoxLayout *vbox1 = new QVBoxLayout;
            vbox1->addWidget(lineEdit);
            vbox1->addWidget(bouton1);
            vbox1->addWidget(bouton2);

            page1->setLayout(vbox1);

            // Page 2

            QProgressBar *progress = new QProgressBar;
            progress->setValue(50);
            QSlider *slider = new QSlider(Qt::Horizontal);
            QPushButton *bouton3 = new QPushButton("Valider");

            QVBoxLayout *vbox2 = new QVBoxLayout;
            vbox2->addWidget(progress);
            vbox2->addWidget(slider);
            vbox2->addWidget(bouton3);

            page2->setLayout(vbox2);

            // Page 3 (je ne vais afficher qu'une image ici, pas besoin de layout)

            page3->setPixmap(QPixmap("icone.png"));
            page3->setAlignment(Qt::AlignCenter);

        // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
        onglets->addTab(page1, "Coordonnées");
        onglets->addTab(page2, "Progression");
        onglets->addTab(page3, "Image");*/


    //FenPrincipale fenetre;

    FenPrincipale2 fenetre;

    fenetre.show();

    return app.exec();
}


#include "MaFenetre.h"

MaFenetre::MaFenetre() : QWidget()
{
    setFixedSize(300, 100);

    // Construction du bouton
    m_bouton = new QPushButton("Quitter", this);

    m_bouton->setFont(QFont("Comic Sans MS", 14));
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->setIcon(QIcon("img/smile.png"));
    m_bouton->move(200, 50);

    // Connexion du clic du bouton à la fermeture de l'application
    QObject::connect(m_bouton, SIGNAL(clicked()), qApp, SLOT(quit()));


    m_lcd = new QLCDNumber(this);
    m_lcd->setSegmentStyle(QLCDNumber::Flat);
    m_lcd->move(50, 20);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(250, 600);
    m_slider->setGeometry(10, 60, 150, 20);

    QObject::connect(m_slider, SIGNAL(valueChanged(int)), m_lcd, SLOT(display(int))) ;
    QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(changerLargeur(int)));
    QObject::connect(this, SIGNAL(agrandissementMax()), qApp, SLOT(quit()));


    m_boutonDialogue = new QPushButton("Ouvrir la boîte de dialogue", this);
    m_boutonDialogue->move(300, 50);

    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(ouvrirDialogue()));
}

void MaFenetre::changerLargeur(int largeur)
{
    setFixedSize(largeur, 100);

    if (largeur == 600)
    {
        emit agrandissementMax();
    }
}

void MaFenetre::ouvrirDialogue()
{
    int reponse = QMessageBox::question(this, "Titre de la fenêtre", "Dites voir, je me posais la question comme cela, êtes-vous vraiment un Zéro ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Interrogatoire", "Alors bienvenue chez les Zéros !");
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::critical(this, "Interrogatoire", "Tricheur ! Menteur ! Voleur ! Ingrat ! Lâche ! Traître !\nSors d'ici ou j'appelle la police !");
    }

    bool ok = false;
    QString pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?", QLineEdit::Normal, QString(), &ok);
    if (ok && !pseudo.isEmpty())
    {
        QMessageBox::information(this, "Pseudo", "Bonjour " + pseudo + ", ça va ?");
    }
    else
    {
        QMessageBox::critical(this, "Pseudo", "Vous n'avez pas voulu donner votre nom… snif.");
    }


    bool ok2 = false;
    QFont police = QFontDialog::getFont(&ok2, m_boutonDialogue->font(), this, "Choisissez une police");
    if (ok2)
    {
        m_boutonDialogue->setFont(police);
    }

    QColor couleur = QColorDialog::getColor(Qt::white, this);

    QPalette palette;
    palette.setColor(QPalette::ButtonText, couleur);
    m_boutonDialogue->setPalette(palette);

    QString dossier = QFileDialog::getExistingDirectory(this);
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
    QString fichier1 = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
}

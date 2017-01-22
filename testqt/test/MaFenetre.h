#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QMessageBox>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>

class MaFenetre : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    MaFenetre();

    public slots:
    void changerLargeur(int largeur);
    void ouvrirDialogue();

    signals:
    void agrandissementMax();

    private:
    QLCDNumber *m_lcd;
    QPushButton *m_bouton;
    QSlider *m_slider;
    QPushButton *m_boutonDialogue;
};

#endif

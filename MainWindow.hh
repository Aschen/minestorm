#ifndef MAINWINDOW_HH
# define MAINWINDOW_HH

# include <QMainWindow>

class Display;

/**
 * @brief La classe MainWindow crée un widget contenant un controller et un gameboard pour le game
 * donné
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Display *display, QWidget *parent = 0);
    ~MainWindow();

private:
};

#endif // MAINWINDOW_HH

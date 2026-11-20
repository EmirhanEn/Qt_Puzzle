#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PuzzlePiece;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onSwapRequested(int fromRow, int fromCol, int toRow, int toCol);

private:
    static const int Size = 5;

    void setupGrid();
    void newGame();
    bool isNeighbor(int r1, int c1, int r2, int c2) const;
    bool isSolved() const;

    Ui::MainWindow *ui;
    PuzzlePiece *m_grid[Size][Size];
    int m_moves = 0;
};
#endif

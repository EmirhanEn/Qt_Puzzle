#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "puzzlepiece.h"

#include <QMessageBox>

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupGrid();
    newGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupGrid()
{
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            auto *piece = static_cast<PuzzlePiece *>(ui->puzzleGrid->itemAtPosition(r, c)->widget());
            piece->setPosition(r, c);
            m_grid[r][c] = piece;
            connect(piece, &PuzzlePiece::swapRequested,
                    this, &MainWindow::onSwapRequested);
        }
    }
}

void MainWindow::newGame()
{
    std::vector<int> ids(Size * Size);
    std::iota(ids.begin(), ids.end(), 0);

    std::mt19937 rng(std::random_device{}());
    do {
        std::shuffle(ids.begin(), ids.end(), rng);
    } while (std::is_sorted(ids.begin(), ids.end()));

    for (int i = 0; i < Size * Size; ++i)
        m_grid[i / Size][i % Size]->setPiece(ids[i]);

    m_moves = 0;
    ui->lblHamle->setNum(m_moves);
}

bool MainWindow::isNeighbor(int r1, int c1, int r2, int c2) const
{
    const int dr = qAbs(r1 - r2);
    const int dc = qAbs(c1 - c2);
    return dr <= 1 && dc <= 1 && !(dr == 0 && dc == 0);
}

bool MainWindow::isSolved() const
{
    for (int r = 0; r < Size; ++r)
        for (int c = 0; c < Size; ++c)
            if (m_grid[r][c]->pieceId() != r * Size + c)
                return false;
    return true;
}

void MainWindow::onSwapRequested(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!isNeighbor(fromRow, fromCol, toRow, toCol))
        return;

    PuzzlePiece *a = m_grid[fromRow][fromCol];
    PuzzlePiece *b = m_grid[toRow][toCol];

    const int temp = a->pieceId();
    a->setPiece(b->pieceId());
    b->setPiece(temp);

    ++m_moves;
    ui->lblHamle->setNum(m_moves);

    if (isSolved()) {
        const auto answer = QMessageBox::question(
            this, "Tebrikler!",
            QString(" Puzzle tamamlandı \n Kullanılan hamle: %1 \n\n Yeni Oyun?").arg(m_moves));
        if (answer == QMessageBox::Yes)
            newGame();
    }
}

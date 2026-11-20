#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

#include <QLabel>

class PuzzlePiece : public QLabel
{
    Q_OBJECT

public:
    explicit PuzzlePiece(QWidget *parent = nullptr);

    void setPosition(int row, int col);
    int row() const { return m_row; }
    int col() const { return m_col; }
    int pieceId() const { return m_pieceId; }

    void setPiece(int id);

signals:
    void swapRequested(int fromRow, int fromCol, int toRow, int toCol);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    int m_row = -1;
    int m_col = -1;
    int m_pieceId = -1;
};

#endif

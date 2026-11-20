#include "puzzlepiece.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QPixmap>

PuzzlePiece::PuzzlePiece(QWidget *parent)
    : QLabel(parent)
{
    setAcceptDrops(true);
}

void PuzzlePiece::setPosition(int row, int col)
{
    m_row = row;
    m_col = col;
}

void PuzzlePiece::setPiece(int id)
{
    m_pieceId = id;
    setPixmap(QPixmap(QString(":/images/%1.png").arg(id)));
}

void PuzzlePiece::mousePressEvent(QMouseEvent *event)
{
    auto *mime = new QMimeData;
    mime->setText(QString("%1,%2").arg(m_row).arg(m_col));

    auto *drag = new QDrag(this);
    drag->setMimeData(mime);
    drag->setPixmap(pixmap().scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    drag->setHotSpot(event->position().toPoint());
    drag->exec(Qt::MoveAction);
}

void PuzzlePiece::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void PuzzlePiece::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void PuzzlePiece::dropEvent(QDropEvent *event)
{
    const QStringList parts = event->mimeData()->text().split(',');
    event->acceptProposedAction();
    emit swapRequested(parts[0].toInt(), parts[1].toInt(), m_row, m_col);
}

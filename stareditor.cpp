#include <QtWidgets>

#include "stareditor.h"
#include "starrating.h"

//! [0]
StarEditor::StarEditor(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);
}
//! [0]

QSize StarEditor::sizeHint() const
{
    return myStarRating.sizeHint();
}

//! [1]
void StarEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    myStarRating.paint(&painter, rect(), this->palette(),
                       StarRating::Editable);
}
//! [1]

//! [2]
void StarEditor::mouseMoveEvent(QMouseEvent *event)
{
    int star = starAtPosition(event->x());

    if (star != myStarRating.starCount() && star != -1) {
        myStarRating.setStarCount(star);
        update();
    }
}
//! [2]

//! [3]
void StarEditor::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit editingFinished();
}
//! [3]

//! [4]
int StarEditor::starAtPosition(int x)
{
    int star = (x / (myStarRating.sizeHint().width()
                     / myStarRating.maxStarCount())) + 1;
    if (star <= 0 || star > myStarRating.maxStarCount())
        return -1;

    return star;
}
//! [4]

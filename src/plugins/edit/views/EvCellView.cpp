#include "EvCellView.h"


#include "EvApplication.h"
#include "EvIconsfactory.h"
#include "EvMainWindow.h"

#include "EvProject.h"
#include "EvCell.h"

#include <QTextEdit>
#include <QVBoxLayout>

struct EvCellViewPrivate {
    EvCell * cell;

};

EvCellView::EvCellView(EvCell * cell,QWidget * parent):
    EvWidget(cell,parent),
    d_ptr(new EvCellViewPrivate)
{
    d_ptr->cell = cell;
    setWindowTitle(cell->objectName());
    setWindowIcon(evApp->iconsFactory()->objectIcon(Ev::Cell,EvIconsFactory::Light));
    setEnabled(true);
    setSupportsRename(true);

    QTextEdit * content = new QTextEdit(this);
    content->setText(windowTitle());
    setContent(content);
}

EvCellView::~EvCellView()
{
    delete d_ptr;
}





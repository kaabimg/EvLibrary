#include "EvEditProjectView.h"


#include "EvProject.h"

#include "EvApplication.h"
#include "EvIconsfactory.h"
#include "EvMainWindow.h"

#include "EvCellView.h"
#include <QTextEdit>

struct EvEditProjectViewPrivate {
    EvProject * project;
};


EvEditProjectView::EvEditProjectView(
        EvProject * project,QWidget * parent):
    EvWidget(project,parent),
    d_ptr(new EvEditProjectViewPrivate)
{
    d_ptr->project = project;
    setWindowTitle(project->objectName());
    setWindowIcon(evApp->iconsFactory()->objectIcon(Ev::Project,EvIconsFactory::Light));
    setEnabled(true);
    setSupportsRename(true);

    QTextEdit * content = new QTextEdit(this);
    content->setText(windowTitle());
    setContent(content);
}

EvEditProjectView::~EvEditProjectView()
{
    delete d_ptr;
}

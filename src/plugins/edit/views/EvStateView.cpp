#include "EvStateView.h"


#include "../../../ezverif/data/circuit/EvState.h"
#include "../../../application/core/base/EvApplication.h"
#include "../../../application/core/settings/EvIconsfactory.h"

#include <QTextEdit>

struct EvStateViewPrivate {
    EvState *state;
};


EvStateView::EvStateView(EvState *state, QWidget *parent) :
    EvWidget(state,parent),
    d_ptr(new EvStateViewPrivate)
{
    d_ptr->state = state;

    setWindowTitle(state->objectName());
    setWindowIcon(evApp->iconsFactory()->objectIcon(Ev::State,EvIconsFactory::Light));
    setEnabled(true);
    setSupportsRename(true);
    QTextEdit * content = new QTextEdit(this);
    content->setText(windowTitle());
    setContent(content);
}

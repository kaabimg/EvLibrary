#include "EvSchematicView.h"
#include "../../../ezverif/data/circuit/EvSchematic.h"
#include "../../../application/core/base/EvApplication.h"
#include "../../../application/core/settings/EvIconsfactory.h"
#include <QTextEdit>

struct EvSchematicViewPrivate {
    EvSchematic * schematic;
};

EvSchematicView::EvSchematicView(EvSchematic * schematic, QWidget *parent) :
    EvWidget(schematic,parent),
    d_ptr(new EvSchematicViewPrivate)
{
    d_ptr->schematic = schematic;
    setWindowTitle(schematic->objectName());
    setWindowIcon(evApp->iconsFactory()->objectIcon(Ev::Schematic,EvIconsFactory::Light));
    setEnabled(true);
    setSupportsRename(true);

    QTextEdit * content = new QTextEdit(this);
    content->setText(windowTitle());
    setContent(content);

}

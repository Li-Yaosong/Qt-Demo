#include "ieditor.h"
#include "editorpage.h"
IEditor::IEditor() {}

void IEditor::initialize()
{
    EditorPage::setUpEditorPage();
}

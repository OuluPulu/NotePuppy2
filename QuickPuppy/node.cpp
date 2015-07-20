#include "node.h"

Node::Node(const QString& aText, QFileInfo& aInfo, Node *aParent)
    : text(aText), parent(aParent), info(aInfo)
{
    if(parent) {
        parent->children.append(this);
    }
}

Node::~Node()
{
    qDeleteAll(children);
}

QVariant Node::data() const {
    return text;
}

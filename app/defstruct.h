#ifndef DEFSTRUCT_H
#define DEFSTRUCT_H
#include <QString>
#include <QVector>
#include <QDebug>
#define Instance(type) \
public: \
    static  type *instance(){ \
        return m_instance ? m_instance : (m_instance = new type());} \
    static void deleteInstance(){ \
        if (m_instance){ \
            delete m_instance; \
            m_instance = nullptr;}} \
private: \
    type(); \
    ~type(); \
    static type *m_instance;

#define InstancePtr(type) \
type *type::m_instance = nullptr;

#define QT_FUNC_NAME \
    QString(QString(Q_FUNC_INFO).section(" ", 0, 0) + " %1::" +QString(Q_FUNC_INFO).section("::", -1)) \
    .arg(metaObject()->className())

enum ActionType
{
    HomePage,
    ProductManage,
    Order,
    GiftPackage,
    AddGoogs
};
#endif // DEFSTRUCT_H

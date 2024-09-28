#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class TextEdit: public QTextEdit
{
    Q_OBJECT
public:
    TextEdit();
    void newFile();                         //新建文件
    bool loadFile(const QString &fileName); //导入文件
    bool save();                            //保存文件
    bool saveAs();                          //另存为文件，最终调用 saveFile
    bool saveFile(QString fileName);        //指定路径保存文件
    //确定是否被保存，在关闭窗口时，提示没有保存文件，防止数据丢失
    bool maybeSave();
    // 确定当前编辑窗口是加载文件 还是新建方式，返回相应全路径
    QString isLocalFile(const QString &fullFileName);
    QString getCurrentFileName();               //返回文件路径，调用isLocalFile
    QString getCurrentFile(){return curFile;}   //返回文件名，不关心该文件是否存在本地文件实体
    //格式字体设置
    void mergeFormationOnWordOrSelection(const QTextCharFormat&format);
    void setAlign(int align);       // 鼠标所在行/所选中内容的对齐方式
    void setListStyle(int style);   // 鼠标所在行/所选中内容对应行的对齐方式
    // 设置当前文件路径、是否命名，在loadFile、saveFile中被调用
    void setCurrentFile(const QString &fileName);

protected:
    // 在关闭前 确定是否保存
    void closeEvent(QCloseEvent *event) override;
    // 监听下列事件、并将对应事件转发给主窗口、主窗口与当前组件不存在继承关系
    // 需要使用到QCoreApplication::sendEvent 传递事件
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    // 通知主窗口刷新 菜单状态
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool event(QEvent *event) override;


private slots:
    void documentIsModified(); // 文档被修改时，给编辑窗口标题加上“*”

private:
    QString curFile;
    bool isUntitled; // 是否命名

};
#endif // TEXTEDIT_H

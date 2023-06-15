#include <QWidget>

namespace typer
{
    namespace gui
    {
        class TypingFinishWidget : public QWidget
        {
            Q_OBJECT
        public:
            TypingFinishWidget(int result, QWidget * parent = nullptr);

        signals:
            void exit();
            void repeat();

        protected:
            void keyPressEvent(QKeyEvent *event) override;
            void showEvent(QShowEvent *event);

        private:
            void buildForm(int result);
        };
    }
}

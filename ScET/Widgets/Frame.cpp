#include "Frame.h"
#include <QtWidgets>
#include "TitleBar.h"


Frame::Frame() {
	m_mouse_down = false;
	setFrameShape(Panel);

	// Make this a borderless window which can't
	// be resized or moved via the window system
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);

	m_titleBar = new TitleBar(this);

	m_content = new QWidget(this);

	QVBoxLayout *vbox = new QVBoxLayout(this);
	vbox->addWidget(m_titleBar);
	vbox->setMargin(0);
	vbox->setSpacing(0);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(m_content);
	layout->setMargin(5);
	layout->setSpacing(0);
	vbox->addLayout(layout);
}

// Allows you to access the content area of the frame
// where widgets and layouts can be added
QWidget* Frame::contentWidget() const { return m_content; }

TitleBar* Frame::titleBar() const { return m_titleBar; }

void Frame::mousePressEvent(QMouseEvent *e) {
	m_old_pos = e->pos();
	m_mouse_down = e->button() == Qt::LeftButton;
}

void Frame::mouseMoveEvent(QMouseEvent *e) {
	int x = e->x();
	int y = e->y();

	if (m_mouse_down) {
		int dx = x - m_old_pos.x();
		int dy = y - m_old_pos.y();

		QRect g = geometry();

		if (left)
			g.setLeft(g.left() + dx);
		if (right)
			g.setRight(g.right() + dx);
		if (bottom)
			g.setBottom(g.bottom() + dy);

		setGeometry(g);

		m_old_pos = QPoint(!left ? e->x() : m_old_pos.x(), e->y());
	} else {
		QRect frame = rect();
		qDebug() << "frame is " << frame;
		qDebug() << "x is " << x << " y is " << y;
		int threshold = 5;
		bool isAtTop = y == 0;
		bool isAtBottom = frame.height() - y <= threshold;
		bool isAtLeft = x <= threshold;
		bool isAtRight = frame.width() - x <= threshold;

		if (isAtTop || isAtBottom) {
			if (isAtLeft) {
				setCursor(Qt::SizeBDiagCursor);
			} else if (isAtRight) {
				setCursor(Qt::SizeFDiagCursor);
			} else {
				setCursor(Qt::SizeVerCursor);
			}
		} else if (isAtLeft || isAtRight) {
			setCursor(Qt::SizeHorCursor);
		} else {
			setCursor(Qt::ArrowCursor);
		}
	}
}

void Frame::mouseReleaseEvent(QMouseEvent *e) {
	m_mouse_down = false;
}
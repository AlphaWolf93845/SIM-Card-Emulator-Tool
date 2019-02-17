#ifndef SEGMENT_H
#define SEGMENT_H

#include <QAbstractButton>

/** A segment class to go into the SegmentedControl
 *
 * @b Description
 * This button subclass draws itself in highlighted, 
 * selected and pressed states. Multiple of these buttons
 * can be combined together to build a segmented button
 * widget which can be very powerful.
 *
 */
class Segment : public QAbstractButton {
	Q_OBJECT

	Q_PROPERTY(bool isPressed READ isPressed)
	Q_PROPERTY(bool isHighlighted READ isHighlighted)
	Q_PROPERTY(bool isSelected READ isSelected WRITE setSelected)

	Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
	Q_PROPERTY(QColor highlightedTextColor READ highlightedTextColor WRITE setHighlightedTextColor)
	Q_PROPERTY(QColor pressedTextColor READ pressedTextColor WRITE setPressedTextColor)
	Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)

	Q_PROPERTY(QFont textFont READ textFont WRITE  setTextFont)

public:
	Segment(QWidget *parent);
	~Segment();

	/**
	 * A boolean value indicating whether or not the button 
	 * has been hovered over and the mouse has been pressed 
 	 * down over it. This is the exact same as the "isDown"
 	 * method on the superclass but it has been renamed and
	 * the aformention method hidden for consistent and more
	 * concise naming.
	 *
	 * @retval	The pressed status of the segment.
	 */
	bool isPressed() const { return isDown(); }

	/**
	 * A boolean value indicating whether or not the button
	 * has been hovered over by the mouse.
	 *
	 * @retval	The hovered status of the segment.
	 */
	bool isHighlighted() const { return highlighted; }

	/**
	 * A boolean value indicating whether or not the button
	 * has been hovered over and the mouse has been pressed
	 * down over it and then released. This is the exact
	 * same as the "isChecked" method on the superclass but 
	 * it has been renamed and the aformention method hidden
	 * for consistent and more concise naming.
	 *
	 * @b Note
	 * Once the segment has been selected by the user it 
	 * cannot be deselected by them. That is to say, when
	 * the user has clicked and released over the segment
	 * and the click has been sucessfully registered, the
	 * button will stop listening for clicks and the segment
	 * will have to be manually deselected using the "setSelected"
	 * method. This is done to stop the segmented control from
	 * being in a state where no segment is selected.
	 *
	 * @retval	The selected status of the segment.
	 */
	bool isSelected() const { return isChecked(); }
	

	/**
	 * The text color of the segment in its default state.
	 * This defaults to black at about 57% opacity.
	 *
	 * @retval	The default color of the text.
	 */
	QColor textColor() const { return m_textColor; }

	/**
	 * The text color of the segment when the mouse has hovered
	 * over it. This defaults to "Qt::black".
	 *
	 * @retval	The color of the highlighted text.
	 */
	QColor highlightedTextColor() const { return m_highlightedTextColor; }

	/**
	 * The text color of the segment when the mouse has hovered
	 * and been pressed (and is still being held down)
	 * over it. This defaults to "Qt::black".
	 *
	 * @retval	The color of the pressed text.
	 */
	QColor pressedTextColor() const { return m_pressedTextColor; }

	/**
	 * The text color of the segment when the mouse has been clicked
	 * over the segment. This defaults to "Qt::black".
	 *
	 * @retval	The color of the selected text.
	 */
	QColor selectedTextColor() const { return m_selectedTextColor; }


	/**
	 * Sets the default text color of the of the button.
	 *
	 * @param color	The new color
	 */
	void setTextColor(const QColor &color) { m_textColor = color; }	

	/**
	 * Sets the highlighted text color of the button.
	 *
	 * @param color	The new color
	 */
	void setHighlightedTextColor(const QColor &color) { m_highlightedTextColor = color; }
	
	/**
	 * Sets the pressed text color of the button.
	 *
	 * @param color	The new color
	 */
	void setPressedTextColor(const QColor &color) { m_pressedTextColor = color; }
	
	/**
	 * Sets the selected text color of the button.
	 *
	 * @param color	The new color
	 */
	void setSelectedTextColor(const QColor &color) { m_selectedTextColor = color; }


	/**
	 * The font of the text. This defaults to "Segoe UI" 
	 * size 11 pt on Windows and "San Francisco" on macOS.
	 *
	 * @retval	The font of the text.
	 */
	QFont textFont() const { return m_textFont; }

	/**
	 * Sets the font of the text.
	 *
	 * @param textFont	The new font.
	 */
	void setTextFont(const QFont &textFont) { m_textFont = textFont; }

	/**
	 * Updates the minimum size of the button taking into
	 * account the current text and font. This method needs
	 * to be called manually every time the text or font is 
	 * updated or unexpected sizing will occur.
	 */
	void sizeToFit();

Q_SIGNALS:
	/**
	 * Emitted when the segment has been selected.
	 */
	void selected();

public Q_SLOTS:
	/**
	 * Sets the selected status of the segment. Setting this
	 * has the same effect as calling setChecked() but that 
	 * method has been hidden for more consistent naming.
	 *
	 * @param selected	The new selected status.
	 */
	void setSelected(const bool &selected);

protected:
	void paintEvent(QPaintEvent *paintEvent) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void mousePressEvent(QMouseEvent *mouseEvent) override;

private:
	bool highlighted = false;
	QFont m_textFont = QFont("Segoe UI", 11);
	QColor m_textColor = QColor(0, 0, 0, 145);
	QColor m_highlightedTextColor, m_pressedTextColor, m_selectedTextColor = Qt::black;
	const int selectedIndicatorHeight = 2;

	// these have been replaced with types above and 
	// are not to be used
	using QAbstractButton::setCheckable;
	using QAbstractButton::isCheckable;
	using QAbstractButton::isChecked;
	using QAbstractButton::setDown;
	using QAbstractButton::isDown;
};

#endif // SEGMENT_H

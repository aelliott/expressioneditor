/*!
 * \file
 * \author Alex Elliott <alex@alex-elliott.co.uk>
 * \version 0.1pre
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009,2010 Alex Elliott <alex@alex-elliott.co.uk>
 *
 * Expression editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Expression editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Expression editor.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "expressioneditor.hpp"

/*!
 * Creates a new ExpressionEditor widget
 *
 * \param   parent  The parent of this widget
 */
ExpressionEditor::ExpressionEditor(QWidget *parent) : QWidget(parent)
{
    // Add the main layout and the splitter between the editors and test
    // widgets
    mainLayout = new QVBoxLayout(this);
    splitter = new QSplitter(Qt::Vertical, this);

    // Add the graphical editor to the top of the window
    graphicalEditor = new GraphicalEditor(this);
    connect(
            graphicalEditor, SIGNAL(expressionChanged(QString)),
            this, SLOT(updateExpression(QString))
           );

    // Add the text editor below the graphical editor
    QWidget *textInput = new QWidget(this);
    QHBoxLayout *textLayout = new QHBoxLayout(textInput);
    QLabel *inputLabel = new QLabel(tr("Expression: "));
    inputLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    expressionInput = new QTextEdit;
    expressionInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // Initialise the height correctly at the start, this will be called again
    // whenever the text changes or a resize event is triggered to ensure the
    // whole expression is visible
    updateInputHeight();

    // Create a syntax highlighter to attach to the text editor
    highlighter = new ExpressionHighlighter(expressionInput);

    // Add the label determining whether the expression is valid or invalid
    validIndicator = new QLabel;

    textLayout->addWidget(inputLabel);
    textLayout->addWidget(expressionInput);
    textLayout->addWidget(validIndicator);

    // Create a layout containing the graphical and text editors to be placed
    // in the splitter
    QWidget *workspaceLayout = new QWidget(this);
    subLayout = new QVBoxLayout(workspaceLayout);
    subLayout->addWidget(graphicalEditor);
    subLayout->addWidget(textInput);

    // Add the test widgets
    tester = new ExpressionTester(this);
        connect(
                expressionInput, SIGNAL(textChanged()),
                this, SLOT(updateExpression())
               );

    splitter->addWidget(workspaceLayout);
    splitter->addWidget(tester);

    mainLayout->addWidget(splitter);
}

/*!
 * Get the expression that is currently in use
 *
 * \return  Returns the expression within the editor
 */
QString ExpressionEditor::getExpression()
{
    return expressionInput->toPlainText();
}

/*!
 * Get the test strings from the testing widget
 *
 * \return  A QStringList containing all of the test strings
 *          used by the default testing widget
 */
QStringList ExpressionEditor::getTestStrings()
{
    return tester->getTestStrings();
}

/*!
 * Reimplemented resize handler, triggers a height update of the regexp text
 * input
 *
 * \param   event   Unused - the resize event triggered
 */
void ExpressionEditor::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    updateInputHeight();
}

/*!
 * Slots for any updates to the regular expression
 */
void ExpressionEditor::updateExpression()
{
    // Check if there is a discrepancy between stored expressions, if so
    // rectify it, otherwise do nothing
    if(getExpression() != tester->getExpression())
        updateExpression(getExpression());
}

/*!
 * Slots for any updates to the regular expression
 */
void ExpressionEditor::updateExpression(QString regex)
{
    // Cascade the update down to the test widgets
    tester->updateExpression(regex);

    // Also cascade the update to the graphical editor, use the response to
    // determine the valid label
    if(graphicalEditor->updateExpression(regex))
    {
        // If the expression is valid (and therefore it is stable) check
        // that the text editor has the correct regular expression, if not
        // update it
        if(getExpression() != regex)
            expressionInput->setText(regex);

        validIndicator->setPixmap(QPixmap(":/images/valid.png"));
        validIndicator->setToolTip(tr("The expression is valid"));
    }
    else
    {
        validIndicator->setPixmap(QPixmap(":/images/invalid.png"));
        validIndicator->setToolTip(graphicalEditor->getErrorString());
    }

    // Trigger a height update in case the text edit has changed and one is
    // required
    updateInputHeight();
}


/*!
 * Adds a test string to the expression test widget
 *
 * \param   testString  The test string to add to the test widget
 */
void ExpressionEditor::addTestString(QString testString)
{
    tester->addTestString(testString);
}

/*!
 * Sets the regexp format
 *
 * \param   type    The regular expression type to pass along
 */
void ExpressionEditor::setRegexpFormat(int type)
{
    // Cascade the change down
    tester->setRegexpFormat(type);
    graphicalEditor->setRegexpFormat(type);
}

/*!
 * Produces a QPixmap of the expression visualisation to export to PNG
 *
 * \param   A QPixmap of the graphical regular expression visualisation
 */
QPixmap ExpressionEditor::exportToImage()
{
    return graphicalEditor->exportToImage();
}

/*!
 * Updates the height of the regexp text input to fit the expression.
 */
void ExpressionEditor::updateInputHeight()
{
    // Set an initial height
    int height = qApp->fontMetrics().height()*2;

    // Determine the width of the expression and attempt to add the correct
    // number of added line heights
    int width = qApp->fontMetrics().width(getExpression());
    while(width+20 > expressionInput->width())
    {
        height += qApp->fontMetrics().height();
        width -= (width + 20);
    }

    // Add another line for each line break found in the expression
    if(getExpression().contains("\n"))
        height += qApp->fontMetrics().height()*getExpression().count("\n");

    // Set the height calculated
    expressionInput->setFixedHeight(height);
}

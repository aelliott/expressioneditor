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

#include "searchreplacetester.hpp"

SearchReplaceTester::SearchReplaceTester(QWidget *parent) : QWidget(parent), type(-1)
{
    layout = new QVBoxLayout(this);

    replaceLayout = new QHBoxLayout;

    replaceLabel = new QLabel(tr("Replace text: "));
    replaceLayout->addWidget(replaceLabel);

    replaceInput = new QLineEdit;
        connect(replaceInput, SIGNAL(textChanged(QString)), this, SLOT(updateReplacedText()));
    replaceLayout->addWidget(replaceInput);

    layout->addLayout(replaceLayout);

    splitter = new QSplitter(Qt::Horizontal);

    testText = new QTextEdit(splitter);
        highlighter = new BlockHighlighter(testText);
        connect(testText, SIGNAL(textChanged()), this, SLOT(updateReplacedText()));
    splitter->addWidget(testText);

    replacedText = new QTextEdit(splitter);
    replacedText->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    splitter->addWidget(replacedText);

    layout->addWidget(splitter);

    setLayout(layout);
}

QString SearchReplaceTester::getText() const
{
    return testText->toPlainText();
}

void SearchReplaceTester::updateExpression(QString exp)
{
    highlighter->updateExpression(exp);
    expression = exp;
    updateReplacedText();
}

void SearchReplaceTester::updateReplacedText()
{
    QString block = testText->toPlainText();
    RegexFactory *factory = new RegexFactory();
    RegexBase *rx = factory->factory(expression, type);

    if(rx->indexIn(block, 0) < 0)
    {
        // no match, no point replacing anything
        replacedText->setText(block);
        return;
    }

    int offset = 0;
    int i = 0;
    int pos = 0;
    while((pos = rx->indexIn(block, offset)) >= 0 && pos <= block.length())
    {
        if(i > 0 && pos == 0 || rx->matchedLength() == 0)
            break;

        int initialLength = block.length();
        int length = rx->matchedLength();

        QString replacement = replaceInput->text();
        for(int l = 0; l < replacement.length(); ++l)
        {
            int len = replacement.length();
            QRegExp backreference("\\\\(\\d+)");
            if(backreference.indexIn(replacement, l) == l)
            {
                int ref = backreference.cap(1).toInt();
                if(ref <= rx->captureCount())
                    replacement.replace(l, backreference.matchedLength(), rx->cap(ref));
                else
                    replacement.replace(l, backreference.matchedLength(), tr("[Unknown Capture: #")
                                                                            + backreference.cap(1)
                                                                            + "]");
                l += replacement.length() - len;
            }
            else if(QString(replacement.at(l)) == "\\") // next character is escaped
                ++l;
        }

        replacedText->setHtml(block.replace(pos, length, QString("<span style='font-weight: bold; color: red;'>") + replacement + "</span>"));
        int newOffset = pos + length + block.length() - initialLength;
        if(newOffset <= offset)
            return;
        else
            offset = newOffset;
        ++i;
    }

    delete rx;
    delete factory;
}

void SearchReplaceTester::setText(QString testString)
{
    testText->setText(testString);
    updateReplacedText();
}

void SearchReplaceTester::setRegexpFormat(int newType)
{
    type = newType;
    highlighter->setRegexpFormat(type);
    updateReplacedText();
}

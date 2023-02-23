/*This is a C++ port of the following PyQt example
http://diotavelli.net/PyQtWiki/Python%20syntax%20highlighting
C++ port by Frankie Simon (docklight.de, www.fuh-edv.de)

The following free software license applies for this file ("X11 license"):

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom KICKPYTHONSYNTAXHIGHLIGHTERthe Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef KICKPYTHONSYNTAXHIGHLIGHTER_H
#define KICKPYTHONSYNTAXHIGHLIGHTER_H


#include <QSyntaxHighlighter>

//! Container to describe a highlighting rule. Based on a regular expression, a relevant match # and the format.
/**diotavelli.net
 * @brief
 *
 */
class HighlightingRule
{
public:
 /**
  * @brief
  *
  * @param patternStr
  * @param n
  * @param matchingFormat
  */
 HighlightingRule(const QString &patternStr, int n, const QTextCharFormat &matchingFormat)
 {
  originalRuleStr = patternStr;
  pattern = QRegExp(patternStr);
  nth = n;
  format = matchingFormat;
 }
 QString originalRuleStr; /**< TODO: describe */
 QRegExp pattern; /**< TODO: describe */
 int nth; /**< TODO: describe */
 QTextCharFormat format; /**< TODO: describe */
};

//! Implementation of highlighting for Python code.
/**
 * @brief
 *
 */
class KickPythonSyntaxHighlighter : public QSyntaxHighlighter
{
 Q_OBJECT
public:
 /**
  * @brief
  *
  * @param parent
  */
 KickPythonSyntaxHighlighter(QTextDocument *parent = nullptr);
protected:
     /**
      * @brief
      *
      * @param text
      */
     void highlightBlock(const QString &text);
private:
 QStringList keywords; /**< TODO: describe */
 QStringList operators; /**< TODO: describe */
 QStringList braces; /**< TODO: describe */

 QHash<QString, QTextCharFormat> basicStyles; /**< TODO: describe */

 /**
  * @brief
  *
  */
 void initializeRules();

 //! Highlighst multi-line strings, returns true if after processing we are still within the multi-line section.
 /**
  * @brief
  *
  * @param text
  * @param delimiter
  * @param inState
  * @param style
  * @return bool
  */
 bool matchMultiline(const QString &text, const QRegExp &delimiter, const int inState, const QTextCharFormat &style);
 /**
  * @brief
  *
  * @param colorName
  * @param style
  * @return const QTextCharFormat
  */
 const QTextCharFormat getTextCharFormat(const QString &colorName, const QString &style = QString());

 QList<HighlightingRule> rules; /**< TODO: describe */
 QRegExp triSingleQuote; /**< TODO: describe */
 QRegExp triDoubleQuote; /**< TODO: describe */
};


#endif // KICKPYTHONSYNTAXHIGHLIGHTER_H

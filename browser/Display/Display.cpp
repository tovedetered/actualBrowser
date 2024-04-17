//
// Created by tobedetered on 4/16/24.
//

#include "Display.h"
std::string Display::lex(const std::string &dom) {
    bool in_tag = false;
    bool in_entity = false;
    std::string tmp;
    std::string lexedDom;
    for (auto c: dom) {
        if (c == '<') {
            in_tag = true;
        } else if (c == '>') {
            in_tag = false;
        } else if (!in_tag) {
            if (c == '&') {
                in_entity = true;
                tmp.push_back(c);
            } else if (!in_entity) {
                lexedDom.push_back(c);
            } else {
                if (c != ';') {
                    if (c != '\n' && c != ' ') {
                        tmp.push_back(c);
                    } else {
                        lexedDom.insert(lexedDom.end(), tmp.begin(), tmp.end());
                        lexedDom.push_back(c);
                        in_entity = false;
                    }
                } else {
                    tmp.push_back(c);
                    if (entityMap.contains(tmp)) {
                        std::string temp = entityMap.at(tmp);
                        lexedDom.insert(lexedDom.end(), temp.begin(), temp.end());
                        tmp.clear();
                    } else {
                        lexedDom.insert(lexedDom.end(), tmp.begin(), tmp.end());
                        tmp.clear();
                    }
                    in_entity = false;
                }
            }
        }
    }
    return lexedDom;
}

void Display::initEntityMap() {
    // Add key-value pairs for browser entities
    entityMap["&lt;"] = "<";
    entityMap["&gt;"] = ">";
    entityMap["&amp;"] = "&";
    entityMap["&quot;"] = "\"";
    entityMap["&apos;"] = "'";
    entityMap["&cent;"] = "¢";
    entityMap["&pound;"] = "£";
    entityMap["&yen;"] = "¥";
    entityMap["&euro;"] = "€";
    entityMap["&nbsp;"] = " ";  // Non-breaking space
    entityMap["&iexcl;"] = "¡"; // Inverted exclamation mark
    entityMap["&cent;"] = "¢";  // Cent sign
    entityMap["&pound;"] = "£"; // Pound sign
    entityMap["&curren;"] = "¤";// Currency sign
    entityMap["&yen;"] = "¥";   // Yen sign
    entityMap["&brvbar;"] = "¦";// Broken vertical bar
    entityMap["&sect;"] = "§";  // Section sign
    entityMap["&uml;"] = "¨";   // Diaeresis
    entityMap["&copy;"] = "©";  // Copyright sign
    entityMap["&ordf;"] = "ª";  // Feminine ordinal indicator
    entityMap["&laquo;"] = "«"; // Left-pointing double angle quotation mark
    entityMap["&not;"] = "¬";   // Not sign
    entityMap["&shy;"] = "­";   // Soft hyphen
    entityMap["&reg;"] = "®";   // Registered trademark sign
    entityMap["&macr;"] = "¯";  // Macron
    entityMap["&deg;"] = "°";   // Degree sign
    entityMap["&plusmn;"] = "±";// Plus-minus sign
    entityMap["&sup2;"] = "²";  // Superscript two
    entityMap["&sup3;"] = "³";  // Superscript three
    entityMap["&acute;"] = "´"; // Acute accent
    entityMap["&micro;"] = "µ"; // Micro sign
    entityMap["&para;"] = "¶";  // Pilcrow sign
    entityMap["&middot;"] = "·";// Middle dot
    entityMap["&cedil;"] = "¸"; // Cedilla
    entityMap["&sup1;"] = "¹";  // Superscript one
    entityMap["&ordm;"] = "º";  // Masculine ordinal indicator
    entityMap["&raquo;"] = "»"; // Right-pointing double angle quotation mark
    entityMap["&frac14;"] = "¼";// Fraction one-quarter
    entityMap["&frac12;"] = "½";// Fraction one-half
    entityMap["&frac34;"] = "¾";// Fraction three-quarters
    entityMap["&iquest;"] = "¿";
    entityMap["&ndash;"] = "–";//Dash
    entityMap["&NotLessGreater;"] = "≸";
    entityMap["&NotLessLess;"] = "≪̸";
    entityMap["&NotLessSlantEqual;"] = "⩽̸";
    entityMap["&NotLessTilde;"] = "≴";
    entityMap["&NotNestedGreaterGreater;"] = "⪢̸";
    entityMap["&NotNestedLessLess;"] = "⪡̸";
    entityMap["&notni;"] = "∌";
    entityMap["&notniva;"] = "∌";
    entityMap["&notnivb;"] = "⋾";
    entityMap["&notnivc;"] = "⋽";
    entityMap["&NotPrecedes;"] = "⊀";
    entityMap["&NotPrecedesEqual;"] = "⪯̸";
    entityMap["&NotPrecedesSlantEqual;"] = "⋠";
    entityMap["&NotReverseElement;"] = "∌";
    entityMap["&NotRightTriangle;"] = "⋫";
    entityMap["&NotRightTriangleBar;"] = "⧐̸";
    entityMap["&NotRightTriangleEqual;"] = "⋭";
    entityMap["&NotSquareSubset;"] = "⊏̸";
    entityMap["&NotSquareSubsetEqual;"] = "⋢";
    entityMap["&NotSquareSuperset;"] = "⊐̸";
    entityMap["&NotSquareSupersetEqual;"] = "⋣";
    entityMap["&NotSubset;"] = "⊂⃒";
    entityMap["&NotSubsetEqual;"] = "⊈";
    entityMap["&NotSucceeds;"] = "⊁";
    entityMap["&NotSucceedsEqual;"] = "⪰̸";
    entityMap["&NotSucceedsSlantEqual;"] = "⋡";
    // Add more key-value pairs as needed
}

/*

MIT License

Copyright (c) 2025 Andrii Hlyvko

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#pragma once


#include <iostream>
#include <sstream>

#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <optional>


// #include "../BinaryTree.h"
// #include "../LinkedList.h"

namespace leetcode_utils {

namespace loggerstream {

struct PrettyBlock {
    std::vector<std::string> lines;
    int width = 0;
};

template <typename T>
std::ostream& printElement(std::ostream& os, const T& val);  // forward decl

template <typename T, typename=void> struct LoggerFormatter {
    // this is the default print trait template
    // it gets used for types who dont have the print trait implemented
    static void print(std::ostream &os, const T& val){
        os << val;
    }
};


template <typename T>
std::ostream& printElement(std::ostream& os, const T& val) {
    LoggerFormatter<T>::print(os, val);
    return os;
}


template <typename T> struct LoggerFormatter<std::vector<T>> {
    static void print(std::ostream& os, const std::vector<T> &vec){
    
    os << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        printElement(os, vec[i]);
        if (i < vec.size() - 1) os << ", ";
    }
    os << "}";
    
    }
    
};



template <typename T, typename V> 
struct LoggerFormatter<std::pair<T,V>> {
    static void print(std::ostream& os, const std::pair<T,V> &pair_val) {
    
    os << "<";
    printElement(os, pair_val.first);
    os << ",";
    printElement(os, pair_val.second);
    os << ">";
}
    
};



template <typename T>
struct LoggerFormatter<std::optional<T>> {
static void print(std::ostream&os, const std::optional<T>& opt) {
    
    if (opt.has_value()) {
        os << "Some(";
        printElement(os, *opt);
        os << ")";
    } else {
        os << "None";
    }
    
}
};


template <typename T> 
struct LoggerFormatter<std::stack<T>> {
    
    static void print(std::ostream& os, const std::stack<T> s) {
    
    os << "[";
    std::vector<T> temp;
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }
    for (int i = temp.size() - 1; i >= 0; --i) {
        printElement(os, temp[i]);
        if (i != 0) os << ", ";
    }
    os << "]";
    
}
    
    
};




template <typename T>
struct LoggerFormatter<std::queue<T>> {
    
static void print(std::ostream& os, std::queue<T> q) {
        
        os << "queue sieze:" << q.size() << " [";
        while (!q.empty()) {
            printElement(os, q.front());
            q.pop();
            if (!q.empty()) os << ", ";
        }
        os << "]";
    }
    
};




template <typename T, typename V>
struct LoggerFormatter<std::unordered_map<T,V>> {
    
static void print(std::ostream& os, const std::unordered_map<T,V> &map) {
        
        os << "{";
        size_t count = 0;
        for (const auto& [key, val] : map) {
            printElement(os, key);
            os << ": ";
            printElement(os, val);
            if (++count < map.size()) os << ", ";
        }
        os << "}";
        
    }
    
};




template <typename T> 
struct LoggerFormatter<std::deque<T>> {
    
static void print(std::ostream& os, const std::deque<T> &d) {
        
        os << "[";
        for (size_t i = 0; i < d.size(); ++i) {
            printElement(os, d[i]);
            if (i < d.size() - 1) os << ", ";
        }
        os << "]";
        
    }
    
};
    
template <typename T>
struct LoggerFormatter<std::priority_queue<T>> {

    static void print(std::ostream& os, const std::priority_queue<T> pq) {
        
        os << "[";
        while (!pq.empty()) {
            printElement(os, pq.top());
            pq.pop();
            if (!pq.empty()) os << ", ";
        }
        os << "]";
        
    }
    
};

    
    
template <typename T> 
struct LoggerFormatter<std::list<T>> {
    
static void print(std::ostream& os, const std::list<T> &l) {
        
        os << "[";
        auto it = l.begin();
        while (it != l.end()) {
            printElement(os, *it);
            if (++it != l.end()) os << ", ";
        }
        os << "]";
        
        
    }
    
};



template <typename T>
struct LoggerFormatter<std::set<T>> {
static void print(std::ostream& os, const std::set<T> &s) {
        
        os << "{";
        size_t count = 0;
        for (const auto& el : s) {
            printElement(os, el);
            if (++count < s.size()) os << ", ";
        }
        os << "}";
        
    }
    
};
    
    // template <typename T, typename V> static std::ostream& printElement(std::ostream& os, const std::map<T,V> &mp);


template <typename T, typename V>
struct LoggerFormatter<std::unordered_set<T,V>> {
    
static void print(std::ostream& os, const std::unordered_set<T,V> &s) {
        
        os << "{";
        size_t count = 0;
        for (const auto& el : s) {
            printElement(os, el);
            if (++count < s.size()) os << ", ";
        }
        os << "}";
        
        
    }
    
};




template <typename T>
struct LoggerFormatter<BinaryTreeNode<T> *> {
    
    static void print(std::ostream &os, BinaryTreeNode<T> * root) {
        printTree(os, root, "", true);
    }
    
    private:
    static void printTree(std::ostream &os, BinaryTreeNode<T>* root,const std::string &indent, bool isRight) {
    if (!root) return;

    if (root->right) {
        printTree(os, root->right, indent + (isRight ? "        " : " |      "), true);
    }

    os << indent;
    if (isRight) {
        os << " /----- ";
    } else {
        os << " \\----- ";
    }
    // std::cout << root->val << std::endl;
    printElement(os, root->val);
    os << "\n";

    if (root->left) {
        printTree(os, root->left, indent + (isRight ? " |      " : "        "), false);
    }
}
    
};




template <typename T>
struct LoggerFormatter<BinaryTreeNode<T>> {
    
    static void print(std::ostream &os, BinaryTreeNode<T> root) {
        printTree(os, root, "", true);
    }
    
    private:
    static void printTree(std::ostream &os, BinaryTreeNode<T> root,const std::string &indent, bool isRight) {
    // if (!root) return;

    if (root.right) {
        printTree(os, *(root.right), indent + (isRight ? "        " : " |      "), true);
    }

    os << indent;
    if (isRight) {
        os << " /----- ";
    } else {
        os << " \\----- ";
    }
    // std::cout << root->val << std::endl;
    printElement(os, root.val);
    os << "\n";

    if (root.left) {
        printTree(os, *(root.left), indent + (isRight ? " |      " : "        "), false);
    }
}
    
};



template <typename T>
struct LoggerFormatter<LinkedListNode<T>> {
    
void print(std::ostream &os,LinkedListNode<T> *head){
    
    os << "List:[";
    
    while(head!=nullptr){
        os << head->val << "  -->  ";
        head = head->next;
    }
    os << "]"<< std::endl;
    
    
}
    
};





enum class LogColor {
  Default,
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,
  BrightBlack,
  BrightRed,
  BrightGreen,
  BrightYellow,
  BrightBlue,
  BrightMagenta,
  BrightCyan,
  BrightWhite
};
enum class LogLevel { kLogWarn, kLogError, kLogInfo, kLogDebug };

struct Style {
  bool bold = false;
  bool underline = false;
  bool italic = false;
  bool print_level_prefix = false;
  bool pretty = false;
  LogColor text_color = LogColor::Default;
};


// ---- Style Manipulators ----
/*
    NOTE: inline constexpr makes these global constants that can be included 
    and used in many compilation units. These objects then function as global tokens/tags
    When LoggerStream gets one of these tokens as input it will change the internal state of the output styling
    The reason why we have these tokens is so that the user does not have to create a styling manipulator object
    every time they need to change the output styiling. They can just do this:
    logger << set_bold << set_underline << set_color(LogColor::Yellow) << "output" << std::endl;
*/
struct SetBold {};
inline constexpr SetBold set_bold;

struct SetUnderline {};
inline constexpr SetUnderline set_underline;

struct ResetStyle {};
inline constexpr ResetStyle reset_style;


struct SetItalic {};
inline constexpr SetItalic set_italic;

struct SetPretty {};
inline constexpr SetPretty set_pretty;

struct SetColor {
    LogColor color;
    explicit SetColor(LogColor c) : color(c) {}
};
inline SetColor set_color(LogColor c) { return SetColor{c}; }

class LoggerStream {
    
    public:
    
    LoggerStream(LogLevel level, std::ostream &out = std::cout);
    
    ~LoggerStream();
    
    
    private:
    
    // centraized dispatcher
    // template <typename T> static std::ostream& printElement(std::ostream& os, const T& val) {
    //     LoggerFormatter<T>::print(os, val);
    //     return os;
    // }
    
    
    
    
    
    public:
    
    LoggerStream& operator<<(SetBold) {
        style_.bold = true;
        return *this;
    }
    
    
    LoggerStream& operator<<(SetItalic) {
        style_.italic = true;
        return *this;
    }
    

    LoggerStream& operator<<(SetUnderline) {
        style_.underline = true;
        return *this;
    }

    LoggerStream& operator<<(SetColor color) {
        style_.text_color = color.color;
        return *this;
    }
    
    
    LoggerStream& operator<<(SetPretty) {
        style_.pretty = true;
        return *this;
    }

    LoggerStream& operator<<(ResetStyle) {
        style_ = Style{};
        return *this;
    }
    
    template <typename T> LoggerStream& operator<<(const T& val) {
        printElement(buffer_, val);
        return *this;
    }
    
    
    LoggerStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        
        // if the std::endl was passed we flush the output
        // std::endl is implemented as a manipulator function: ostream& endl(ostream &os)
        // we are comparing manip to the function address of std::endl
        if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
            flushToStream();
            style_ = Style{};
        }
        return *this;
    }
    
    
    private:
    
    static std::string BuildAnsiStyle(LogLevel level, const Style &style);
    
    void flushToStream();
    
    LogLevel log_level_{LogLevel::kLogInfo};
    std::ostream& out_stream_;
    Style style_;
    std::ostringstream buffer_;
};

}; // namespace loggerstream

}; // namespace leetcode_utils
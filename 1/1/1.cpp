#include <iostream>
#include <string>
#include <iostream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(std::shared_ptr<Text> text) : text_(text) {}
protected:
    std::shared_ptr<Text> text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::string rev_data = " ";
        for (int i = data.length(); i > -1; --i) {
            rev_data += data[i];
        }
        text_->render(rev_data);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string link, const std::string& data) const {
        std::cout << "<a href=" << link << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

int main()
{
    auto text_block = std::make_shared <Link>(std::make_shared <Reversed>(std::make_shared <Text>()));
    text_block->render("netology.ru", "Hello World!");
}
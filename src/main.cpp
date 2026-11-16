#include "DocumentProcessor.h"
#include "Engine.h"
#include "Wrapper.h"
#include <iostream>
#include <string>

class Subject {
public:
    int func(int arg1, int arg2) const {
        return arg1 + arg2;
    }
};

int main() {
    Subject subj;
    Wrapper wrapper(&subj, &Subject::func, {{"arg1", 0}, {"arg2", 0}});
    Engine engine;
    engine.register_command(&wrapper, "command_name");
    std::cout << engine.execute("command_name", {{"arg1", 4}, {"arg2", 5}}) << '\n';
    DocumentProcessor doc("hello world. this is a simple test! c++ is great.");
    Wrapper w_replace(&doc, &DocumentProcessor::replace_word, {
        {"target", std::string("simple")},
        {"replacement", std::string("modern")}
    });
    Wrapper w_find(&doc, &DocumentProcessor::find_phrase, {
        {"phrase", std::string("test")}
    });
    Wrapper w_cap_words(&doc, &DocumentProcessor::capitalize_words, {});
    Wrapper w_cap_sentences(&doc, &DocumentProcessor::capitalize_sentences, {});
    Wrapper w_num_sentences(&doc, &DocumentProcessor::number_sentences, {});
    engine.register_command(&w_replace, "replace");
    engine.register_command(&w_find, "find");
    engine.register_command(&w_cap_words, "cap_words");
    engine.register_command(&w_cap_sentences, "cap_sentences");
    engine.register_command(&w_num_sentences, "num_sentences");
    std::cout << "Поиск: " << engine.execute("find", {{"phrase", "simple test"}}) << '\n';
    std::cout << "Замена: " << engine.execute("replace", {{"replacement", "powerful"}}) << '\n';
    std::cout << "Заглавные в предложениях: " << engine.execute("cap_sentences") << '\n';
    std::cout << "Нумерация:\n" << engine.execute("num_sentences") << '\n';
    std::cout << "Заглавные в словах:\n" << engine.execute("cap_words") << '\n';
    return 0;
}

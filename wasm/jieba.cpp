#include "cppjieba/Jieba.hpp"

#ifndef EM_PORT_API
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#include <emscripten/bind.h>
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#else
#define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#endif
#else
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype
#else
#define EM_PORT_API(rettype) rettype
#endif
#endif
#endif

using namespace std;
using namespace cppjieba;
using namespace emscripten;

const char *const DICT_PATH = "../dict/jieba.dict.utf8";
const char *const HMM_PATH = "../dict/hmm_model.utf8";
const char *const USER_DICT_PATH = "../dict/user.dict.utf8";
const char *const IDF_PATH = "../dict/idf.utf8";
const char *const STOP_WORD_PATH = "../dict/stop_words.utf8";

Jieba jieba(DICT_PATH,
            HMM_PATH,
            USER_DICT_PATH,
            IDF_PATH,
            STOP_WORD_PATH);

// EM_PORT_API(vector<KeywordExtractor::Word>)
vector<string> ExtractWord(string s, size_t topN)
{
    clock_t start = clock();
    // vector<KeywordExtractor::Word> keywordres;
    vector<string> words;
    jieba.extractor.Extract(s, words, topN);
    // for (auto keyword : keywordres)
    // {
    //     words.push_back(keyword.word);
    // }
    clock_t finish = clock();
    double cost = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "onExtract " << cost << endl;
    return words;
}

vector<string> CutForSearch(string s, bool hmm = true)
{
    vector<string> words;
    jieba.CutForSearch(s, words, hmm);
    return words;
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("ExtractWord", &ExtractWord);
    emscripten::function("CutForSearch", &CutForSearch);
    register_vector<string>("vector<string>");
}
